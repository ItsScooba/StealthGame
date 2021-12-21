#include "Engine.h"

#include <iostream>

#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>

#include "ResourceManager.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "AnimationSystem.h"
#include "AI_System.h"

#include "../../src/DefaultGameScene.h"






//Forward Declares.
void PrintDebug( const int& numUpdatesInDelta, const int& numRendersInDelta, const double& timeDelta );







Engine::Engine()
{
}




Engine::~Engine()
{

}




bool Engine::Initialize()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) return false;

	if ( !m_applicationWindow.Load( 1280, 720 ) ) return false;
	if ( !m_renderer.Initialize() ) return false;

	if ( !m_inputManager.Initialize() ) return false;


	//Load basic shader programs used to display anything to the screen.
	if( !ResourceManager::GetInstance().LoadShader( "DefaultShader", "DefaultVertexShader", "DefaultFragmentShader" ) ) return false;
	if( !ResourceManager::GetInstance().LoadShader( "DefaultSpriteShader", "DefaultSpriteVertexShader", "DefaultSpriteFragmentShader" ) ) return false;


	//Initialize core sub systems for any type of application running in the engine.
	if ( !InitSubsystem( new RenderSystem() ) ) return false;
	if ( !InitSubsystem( new PhysicsSystem() ) ) return false;
	if ( !InitSubsystem( new AnimationSystem() ) ) return false;
	if ( !InitSubsystem( new AI_System() ) ) return false;

	// ADD SYSTEMS BEFORE HERE, OR OBJECTS WON'T BE ADDED TO THEM
	//Initialize Game Scene. 
	if( !SetGameScene( new DefaultGameScene() ) ) return false;

	return true;
}




void Engine::Shutdown()
{
	m_gameScene->Quit();
	m_gameScene->Shutdown();

	//Shutdown any active subsystems.
	while ( !m_activeSubsystems.empty() ) {
		m_activeSubsystems.front()->Shutdown();
		m_activeSubsystems.erase( m_activeSubsystems.begin() );
	}

	m_renderer.Shutdown();
 
	m_applicationWindow.Destroy();

	SDL_Quit();
}




void Engine::Run()
{
	//Some variables used to keep the timing of the game loop.
	const int targetFPS = 60;
	const double MS_PER_UPDATE = ( 1.0 / targetFPS ) * 1000;
	double previousTime = SDL_GetTicks();
	double gameTimeLag = 0.0;								//How far behind the game state and clock is from real time.



	//Debug Variables.
	int ticksSinceDisplayUpdate = 0;
	int rendersSinceDisplayUpdate = 0;
	double previousDebugDisplayTime = 0.0;

	//The SDL Event Loop, where the main game loop runs.
	while ( m_gameScene->IsRunning() ) {
	
		double currentTime = SDL_GetTicks();
		double elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		gameTimeLag += elapsedTime;

		//Process any SDL events and turn them into events the game will understand.
		ProcessSDLEvents();

		//Update the game until it's caught up to real world time.
		while ( gameTimeLag >= MS_PER_UPDATE ) {

			float deltaTime = elapsedTime / 1000.0f;

			m_gameScene->Update();

			for ( std::shared_ptr< I_System > subSystem : m_activeSubsystems ) {
				subSystem->Update( deltaTime );
			}

			gameTimeLag -= MS_PER_UPDATE;
			ticksSinceDisplayUpdate++;
		}

		//After the game has caught up, render it.
		m_renderer.RenderScene( m_gameScene->GetPlayerController()->GetCamera() );
		m_applicationWindow.SwapBuffers();
		
		
		
		
		rendersSinceDisplayUpdate++;


		double displayTimeDelta = ( currentTime - previousDebugDisplayTime ) / 1000.0;
		if ( displayTimeDelta >= 1.0 ) {

			if( m_gameScene->GetPlayerController() != NULL && m_gameScene->GetPlayerController()->GetCursor() != NULL ) {
				std::cout << "Cursor Position: (" << m_gameScene->GetPlayerController()->GetCursor()->GetPositionX() << ", " << 
					m_gameScene->GetPlayerController()->GetCursor()->GetPositionY() << " )" << std::endl;
			}

			std::cout << "FPS: " << rendersSinceDisplayUpdate / displayTimeDelta << ",    UPS: " << ticksSinceDisplayUpdate / displayTimeDelta 
				<< std::endl;
			previousDebugDisplayTime = currentTime;
			rendersSinceDisplayUpdate = 0;
			ticksSinceDisplayUpdate = 0;
		}
	}
}




void Engine::ProcessSDLEvents()
{
	SDL_Event evnt;
	while ( SDL_PollEvent( &evnt ) ) {

		//Check which type of event this is, and process accordingly.
		if ( evnt.type == SDL_QUIT ) {
			Shutdown();
			continue;
		}

		//Check if the input handler can consume the event.
		if ( m_inputManager.HandleEvent( evnt ) )
			continue;

	}
}




bool Engine::InitSubsystem( I_System* subSystem )
{
	if ( !subSystem->Initialize() ) 
		return false;

	m_activeSubsystems.push_back( std::shared_ptr< I_System >( subSystem ) );
	return true;
}




void Engine::ShutdownSubsystem( SystemType systemType )
{
	for ( std::vector< std::shared_ptr< I_System > >::iterator systemIter = m_activeSubsystems.begin(); systemIter != m_activeSubsystems.end(); systemIter++ ) {
		if ( systemIter->get()->system_type == systemType ) {
			systemIter->get()->Shutdown();
			m_activeSubsystems.erase( systemIter );
			return;
		}
	}
}




//Set the active Game Scene.
bool Engine::SetGameScene( GameScene* gameScene )
{
	m_gameScene = std::shared_ptr< GameScene >( gameScene );
	if ( !m_gameScene->Initialize() ) 
		return false;

	return true;
}
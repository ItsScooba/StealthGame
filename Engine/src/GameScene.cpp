#include "GameScene.h"

#include "Engine.h"
#include "ResourceManager.h"







GameScene::GameScene()
{
	m_isRunning = false;
}




GameScene::~GameScene()
{
}




void GameScene::Quit()
{
	m_isRunning = false;
}




//Initialize and Load the game and it's game state.
bool GameScene::Initialize()
{

	if ( !m_gameWorld.Initialize() ) return false;

	m_playerController.reset( new PlayerController() );
	if ( !m_playerController->Initialize() ) return false;


	m_isRunning = true;
	return true;
}




//Shutdown the game logic and game state, and perform any 
void GameScene::Shutdown()
{
	m_isRunning = false;
	m_gameWorld.Shutdown();
}




//Update the game state.
void GameScene::Update()
{

}
#include "DefaultGameScene.h"

#include <iostream>

#include "Engine.h"
#include "ResourceManager.h"
#include "Sprite.h"

#include "ActorFactory.h"

#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "WeaponComponent.h"

#include "Animation.h"
#include "CubeMesh.h"

#include "WeaponsSystem.h"

















DefaultGameScene::DefaultGameScene() : GameScene()
{
}




DefaultGameScene::~DefaultGameScene()
{
}




bool DefaultGameScene::Initialize()
{
	if ( !GameScene::Initialize() ) 
		return false;

	Engine::GetInstance().InitSubsystem( new WeaponsSystem() );

	if ( !ResourceManager::GetInstance().LoadTexture( "Buildings" ) ) return false;
	if ( !ResourceManager::GetInstance().LoadTexture( "EnvironmentProps" ) ) return false;
	if ( !ResourceManager::GetInstance().LoadTexture( "Character_Idle_Sprite" ) ) return false;


	m_playerController->GetCamera().SetPitchDegrees( -90.0f );
	m_playerController->GetCamera().Translate( glm::vec3( 0.0f, 0.0f, 0.0f ) );

	std::shared_ptr< GameObject > playerActor = ActorFactory::CreatePlayerActor();
	m_playerController->PossessEntity( playerActor );
	
	std::shared_ptr< GameObject > playerWeapon = ActorFactory::CreateWeaponObject();
	playerWeapon->AttachTo( playerActor, "Weapon_Socket" );

	std::shared_ptr< GameObject > monsterActor = ActorFactory::CreateMonsterActor();

	m_gameWorld.SpawnEntity( playerActor );
	m_gameWorld.SpawnEntity( monsterActor );
	m_gameWorld.SpawnEntity( playerWeapon );

	return true;
}




void DefaultGameScene::Shutdown()
{
	ResourceManager::GetInstance().UnloadTexture( "Character_Idle_Sprite" );
	ResourceManager::GetInstance().UnloadTexture( "EnvironmentProps" );
	ResourceManager::GetInstance().UnloadTexture( "Buildings" );

	GameScene::Shutdown();
}




void DefaultGameScene::Update()
{
	GameScene::Update();

	m_playerController->ProcessInput( Engine::GetInstance().GetInputManager().GetInputQueue() );
	
	//Update the game world.
	m_playerController->Tick();
	m_gameWorld.Tick();
}
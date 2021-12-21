#include "ActorFactory.h"

#include "Engine.h"

#include "CubeMesh.h"

#include "FixtureUserData.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "AI_Component.h"

#include "WeaponComponent.h"
#include "HealthComponent.h"


#include "SingleShotFireMode.h"












ActorFactory::ActorFactory()
{
}




ActorFactory::~ActorFactory()
{
}




std::shared_ptr< GameObject > ActorFactory::CreatePlayerActor()
{
	static const glm::vec3 playerDimensions( 32.0f, 64.0f, 32.0f );
	std::shared_ptr< GameObject > playerActor( new GameObject() );
	playerActor->SetLocalPosition( glm::vec3( 400.0f + ( playerDimensions.x / 2.0f ), 64.0f, 64.0f + ( playerDimensions.z / 2.0f ) ) );

	b2BodyDef playerBodyDefinition;
	playerBodyDefinition.type = b2_dynamicBody;
	playerBodyDefinition.angle = 0;
	playerBodyDefinition.bullet = true;

	b2PolygonShape playerFixtureShape;
	playerFixtureShape.SetAsBox( playerDimensions.x / 2.0f, playerDimensions.z / 2.0f );
	

	FixtureUserData* fixtureUserData = new FixtureUserData( playerActor );
	b2FixtureDef playerShapeDefinition;
	playerShapeDefinition.shape = &playerFixtureShape;
	playerShapeDefinition.userData = fixtureUserData;

	std::shared_ptr< PhysicsComponent > playerPhysicsComponent( 
		new PhysicsComponent( playerActor, Engine::GetInstance().GetGameScene()->GetWorld().physics_simulation->CreateBody( &playerBodyDefinition ) ) );
	playerPhysicsComponent->physics_body->CreateFixture( &playerShapeDefinition );
	playerActor->AddComponent( playerPhysicsComponent );

	std::shared_ptr< CubeMesh > playerMesh( new CubeMesh( playerDimensions.x, playerDimensions.y, playerDimensions.z ) );
	playerMesh->GetMaterial()->SetBaseMaterialColor( 0.0f, 0.3f, 1.0f, 1.0f );
	playerMesh->GetMaterial()->AddMaterialParameter( "materialColor", std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor", 0.0f, 0.3f, 1.0f, 1.0f ) ) );
	playerActor->AddComponent( std::shared_ptr< RenderComponent >( new RenderComponent( playerActor, playerMesh, true ) ) );






	//===============
	//ANIMATION DATA
	//===============

	std::shared_ptr< AnimationPose > playerBasePose( new AnimationPose() );
	playerBasePose->socket_transforms.emplace( std::pair< std::string, socket_transform >( "Weapon_Socket",
		socket_transform( glm::vec3( 16.0f, 32.0f, playerDimensions.z ), glm::vec3( 0.0f, 0.0f, 0.0f ) ) ) );

	std::shared_ptr< AnimationComponent > animationComponent( new AnimationComponent( playerActor, playerBasePose ) );
	animationComponent->skeletal_data.AddSocket( new Socket( "Weapon_Socket", glm::vec3( 16.0f, 32.0f, playerDimensions.z ) ) );


	std::shared_ptr< AnimationPose > attackPoseStart( new AnimationPose() );
	attackPoseStart->socket_transforms.emplace( "Weapon_Socket", std::pair< glm::vec3, glm::vec3 >( glm::vec3( 16.0f, 32.0f, 32.0f + 8.0f ), glm::vec3( 0.0f, 40.0f, 0.0f ) ) );

	std::shared_ptr< AnimationPose > attackPoseTwo( new AnimationPose() );
	attackPoseTwo->socket_transforms.emplace( "Weapon_Socket", std::pair< glm::vec3, glm::vec3 >( glm::vec3( 16.0f, 32.0f, 32.0f + 8.0f ), glm::vec3( 0.0f, 20.0f, 0.0f ) ) );

	std::shared_ptr< AnimationPose > attackPoseMiddle( new AnimationPose() );
	attackPoseMiddle->socket_transforms.emplace( "Weapon_Socket", std::pair< glm::vec3, glm::vec3 >( glm::vec3( 16.0f, 32.0f, 32.0f + 8.0f ), glm::vec3( 0.0f, -20.0f, 0.0f ) ) );

	std::shared_ptr< AnimationPose > attackPoseEnd( new AnimationPose() );
	attackPoseEnd->socket_transforms.emplace( "Weapon_Socket", std::pair< glm::vec3, glm::vec3 >( glm::vec3( 16.0f, 32.0f, 32.0f + 8.0f ), glm::vec3( 0.0f, -40.0f, 0.0f ) ) );


	std::shared_ptr< Animation > attackAnimation( new Animation() );
	attackAnimation->AddKeyFrame( std::shared_ptr< KeyFrame >( new KeyFrame( 0.04f, attackPoseStart ) ) );
	attackAnimation->AddKeyFrame( std::shared_ptr< KeyFrame >( new KeyFrame( 0.04f, attackPoseTwo ) ) );
	attackAnimation->AddKeyFrame( std::shared_ptr< KeyFrame >( new KeyFrame( 0.04f, attackPoseMiddle ) ) );
	attackAnimation->AddKeyFrame( std::shared_ptr< KeyFrame >( new KeyFrame( 0.4f, attackPoseEnd ) ) );
	animationComponent->AddAnimation( "Swing_Weapon", attackAnimation );

	playerActor->AddComponent( animationComponent );

	return playerActor;
}




std::shared_ptr< GameObject > ActorFactory::CreateMonsterActor()
{
	const static glm::vec3 monsterDimensions( 128.0f, 128.0f, 128.0f );
	std::shared_ptr< GameObject > monsterActor( new GameObject() );
	monsterActor->SetLocalPosition( glm::vec3( 384.0f, 64.0f, 256.0f ) );





	//Physics Body
	b2BodyDef monsterBodyDefinition;
	monsterBodyDefinition.type = b2_kinematicBody;
	monsterBodyDefinition.angle = 0;
	monsterBodyDefinition.bullet = true;

	b2PolygonShape monsterShape;
	monsterShape.SetAsBox( monsterDimensions.x / 2.0f, monsterDimensions.z / 2.0f );

	FixtureUserData* fixtureUserData = new FixtureUserData( monsterActor );

	b2FixtureDef monsterBodyFixtureDefinition;
	monsterBodyFixtureDefinition.shape = &monsterShape;
	monsterBodyFixtureDefinition.userData = fixtureUserData;
	 
	std::shared_ptr< PhysicsComponent > monsterPhysics( 
		new PhysicsComponent( monsterActor, Engine::GetInstance().GetGameScene()->GetWorld().physics_simulation->CreateBody( &monsterBodyDefinition ) ) );
	monsterPhysics->physics_body->CreateFixture( &monsterBodyFixtureDefinition );
	monsterActor->AddComponent( monsterPhysics );
	




	//Mesh
	std::shared_ptr< CubeMesh > monsterMesh( new CubeMesh( monsterDimensions.x, monsterDimensions.y, monsterDimensions.z ) );
	monsterMesh->GetMaterial()->SetBaseMaterialColor( 1.0f, 0.0f, 0.0f, 1.0f );
	monsterMesh->GetMaterial()->AddMaterialParameter( "materialColor", std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor", 1.0f, 0.0f, 0.0f, 1.0f ) ) );
	std::shared_ptr< RenderComponent > monsterRenderComponent( new RenderComponent( monsterActor, monsterMesh ) );
	monsterActor->AddComponent( monsterRenderComponent );

	

	//Misc.
	monsterActor->AddComponent( std::shared_ptr< HealthComponent >( new HealthComponent( monsterActor, 100 ) ) );

	std::shared_ptr< AI_Controller > monsterController( new AI_Controller() );
	monsterController->PossessEntity( monsterActor );
	monsterActor->AddComponent( std::shared_ptr< AI_Component >( new AI_Component( monsterActor, monsterController ) ) );

	return monsterActor;
}




std::shared_ptr< GameObject > ActorFactory::CreateWeaponObject()
{
	std::shared_ptr< GameObject > weaponObject( new GameObject() );
	weaponObject->SetDimensions( glm::vec3( 8.0f, 8.0f, 64.0f ) );
	weaponObject->SetAnchorPosition( glm::vec3( 0.0f, 0.0f, -( weaponObject->GetDimensions().z / 2.0f ) ) );

	std::shared_ptr< CubeMesh > weaponMesh( new CubeMesh( weaponObject->GetDimensions().x, weaponObject->GetDimensions().y, weaponObject->GetDimensions().z ) );
	weaponMesh->GetMaterial()->AddMaterialParameter( "materialColor", std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor", 0.8f, 0.8f, 0.8f, 1.0f ) ) );
	weaponObject->AddComponent( std::shared_ptr< RenderComponent >( new RenderComponent( weaponObject, weaponMesh ) ) );

	
	std::shared_ptr< WeaponComponent > weaponComponent( new WeaponComponent( weaponObject ) );
	weaponComponent->fire_mode = std::shared_ptr< FireMode >( new SingleShotFireMode( weaponComponent ) );
	weaponObject->AddComponent( weaponComponent );



	return weaponObject;
}
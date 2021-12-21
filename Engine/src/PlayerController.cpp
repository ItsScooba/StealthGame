#include "PlayerController.h"

#include "Engine.h"

#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "WeaponComponent.h"










PlayerController::PlayerController()
	: m_playerMovementSpeed( 64.0f )
{

}




PlayerController::~PlayerController()
{

}




bool PlayerController::Initialize()
{
	std::shared_ptr< InputAxis > actorMoveRightAxis( new InputAxis( fastdelegate::MakeDelegate( this, &PlayerController::MoveActorRight ) ) );
	std::shared_ptr< InputAxis > actorMoveForwardAxis( new InputAxis( fastdelegate::MakeDelegate( this, &PlayerController::MoveActorForward ) ) );
	actorMoveRightAxis->BindInputMapping( "MovePlayerLeft", -1.0f );
	actorMoveRightAxis->BindInputMapping( "MovePlayerRight", 1.0f );
	actorMoveForwardAxis->BindInputMapping( "MovePlayerForward", 1.0f );
	actorMoveForwardAxis->BindInputMapping( "MovePlayerBackward", -1.0f );

	m_inputContext.BindInputAxis( actorMoveForwardAxis );
	m_inputContext.BindInputAxis( actorMoveRightAxis );
	
	std::shared_ptr< InputAction > attackAction( new InputAction( "Attack",
		fastdelegate::MakeDelegate( this, &PlayerController::OnAttackStart ), fastdelegate::MakeDelegate( this, &PlayerController::OnAttackEnd ) ) );
	m_inputContext.BindInputAction( attackAction );

	std::shared_ptr< InputAction > sprintAction( new InputAction( "Sprint", 
		fastdelegate::MakeDelegate( this, &PlayerController::OnSprintStart ), fastdelegate::MakeDelegate( this, &PlayerController::OnSprintEnd ) ) );
	m_inputContext.BindInputAction( sprintAction );

	if ( !m_userInterface.Initialize() ) return false;

	m_mouseCursor.reset( new Cursor() );
	if( !m_mouseCursor->SetTexture( "Default_Cursor" ) ) return false;
	m_userInterface.AddWidget( m_mouseCursor );
	
	return true;
}




void PlayerController::Unload()
{
	m_userInterface.Shutdown();
}




void PlayerController::Tick()
{
	//Rotate the player to face the direction they are aiming.
	UpdatePlayerActorRotation();
}




void PlayerController::ProcessInput( std::vector< InputEvent >& inputQueue )
{
	m_inputContext.ProcessInput( inputQueue );
	m_userInterface.Tick();
}




//Update the player actor's rotation so that they are facing in the direction the player is aiming.
void PlayerController::UpdatePlayerActorRotation()
{
	//Get the cursor's position projected into the game world.
	glm::vec2 mouseWorldPosition( m_mouseCursor->GetPositionX() + m_camera.GetPosition().x, 
		m_mouseCursor->GetPositionY() + m_camera.GetPosition().y );
	
	//Get the direction between the player and the mouse cursor.
	glm::vec2 aimDirection( glm::vec2( m_possessedEntity->GetWorldPosition().x, m_possessedEntity->GetWorldPosition().z ) - mouseWorldPosition );

	float targetRotation = glm::atan( aimDirection.x * DEGREES_TO_RADIANS, aimDirection.y * DEGREES_TO_RADIANS );

	m_possessedEntity->SetLocalRotation( glm::vec3( m_possessedEntity->GetLocalRotation().x, ( targetRotation * RADIANS_TO_DEGREES ) - 180.0f, m_possessedEntity->GetLocalRotation().z ) );

	std::shared_ptr< PhysicsComponent > playerPhysicsComponent = std::static_pointer_cast< PhysicsComponent >( m_possessedEntity->GetComponent( ComponentType::c_PHYSICS ) );
	playerPhysicsComponent->physics_body->SetTransform( playerPhysicsComponent->physics_body->GetPosition(), -targetRotation );
}




//Move the player's character along the z-axis ( forward - backward )
void PlayerController::MoveActorForward( float scalar )
{
	if ( m_possessedEntity == nullptr ) return;
	float velocityScalar = scalar * m_playerMovementSpeed;

	//Get the players' physics component.
	std::shared_ptr< PhysicsComponent > playerPhysics = std::static_pointer_cast< PhysicsComponent >( m_possessedEntity->GetComponent( ComponentType::c_PHYSICS ) );
	playerPhysics->physics_body->SetLinearVelocity( b2Vec2( playerPhysics->physics_body->GetLinearVelocity().x, velocityScalar ) );
}




//Move the player along the x-axis ( right-left )
void PlayerController::MoveActorRight( float scalar )
{
	if ( m_possessedEntity == nullptr ) return;
	float velocityScalar = scalar * m_playerMovementSpeed;

	//Get the players' physics component.
	std::shared_ptr< PhysicsComponent > playerPhysics = std::static_pointer_cast< PhysicsComponent >( m_possessedEntity->GetComponent( ComponentType::c_PHYSICS ) );
	playerPhysics->physics_body->SetLinearVelocity( b2Vec2( velocityScalar, playerPhysics->physics_body->GetLinearVelocity().y ) );
}




//Execute actions for when the player first begins attacking.
void PlayerController::OnAttackStart()
{
	if( m_possessedEntity == NULL ) 
		return;

	//Get the game object attached to the player's weapon socket.
	std::shared_ptr< GameObject > childWeaponObject = NULL;
	for( std::shared_ptr< GameObject > child : m_possessedEntity->GetChildren() ) {
		if( child->GetAttachedSocketName() == "Weapon_Socket" ) {
			childWeaponObject = child;
			break;
		}
	}

	if( childWeaponObject == NULL )
		return;

	//Try to fire the weapon and start any animations related to it.
	std::shared_ptr< WeaponComponent > weaponComponent = std::static_pointer_cast< WeaponComponent >( childWeaponObject->GetComponent( ComponentType::c_WEAPON ) );
	if( weaponComponent->fire_mode->CanFire() ) {

		//Play the animation related to firing this weapon.
		std::shared_ptr< AnimationComponent > animationComponent = std::static_pointer_cast< AnimationComponent >( m_possessedEntity->GetComponent( ComponentType::c_ANIMATION ) );
		animationComponent->PlayAnimation( "Swing_Weapon" );

		


		//Fire the weapon and perform any hit tests.
		weaponComponent->fire_mode->BeginFire( animationComponent->GetActiveAnimation()->GetAnimationLength() );
	}
}




//Execute actions for when the player stops attacking.
void PlayerController::OnAttackEnd()
{
	if( m_possessedEntity == NULL )
		return;

	//Get the game object attached to the player's weapon socket.
	std::shared_ptr< GameObject > childWeaponObject = NULL;
	for( std::shared_ptr< GameObject > child : m_possessedEntity->GetChildren() ) {
		if( child->GetAttachedSocketName() == "Weapon_Socket" ) {
			childWeaponObject = child;
			break;
		}
	}

	if( childWeaponObject == NULL )
		return;

	//Try to fire the weapon and start any animations related to it.
	std::shared_ptr< WeaponComponent > weaponComponent = std::static_pointer_cast< WeaponComponent >( childWeaponObject->GetComponent( ComponentType::c_WEAPON ) );
	weaponComponent->fire_mode->EndFire();
}




//Handle when the player presses down the sprint button.
void PlayerController::OnSprintStart()
{
	m_playerMovementSpeed = 128.0f;
}




//Handle when the player releases the sprint button.
void PlayerController::OnSprintEnd()
{
	m_playerMovementSpeed = 64.0f;
}
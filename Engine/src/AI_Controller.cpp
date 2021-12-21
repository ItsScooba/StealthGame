#include "AI_Controller.h"

#include "Engine.h"

#include "PhysicsComponent.h"













AI_Controller::AI_Controller()
{

}




AI_Controller::~AI_Controller()
{

}




//Initialize the AI_Controller
bool AI_Controller::Initialize()
{

	return true;
}




//Shutdown the AI_Controller.
void AI_Controller::Unload()
{

}




//Update the AI_Controller.
void AI_Controller::Tick()
{
	//Update the possessed actor's rotation to face the player.
	UpdateActorRotation();
}




//Update the actors' rotation to face the player character.
void AI_Controller::UpdateActorRotation()
{
	std::shared_ptr< GameObject > playerActor = Engine::GetInstance().GetGameScene()->GetPlayerController()->GetPossessedEntity();
	if( playerActor == NULL ) 
		return;

	glm::vec2 targetPosition( playerActor->GetWorldPosition().x, playerActor->GetWorldPosition().z );

	//Get the direction between the player and the mouse cursor.
	glm::vec2 aimDirection( glm::vec2( m_possessedEntity->GetWorldPosition().x, m_possessedEntity->GetWorldPosition().z ) - targetPosition );

	float targetRotation = glm::atan( aimDirection.x * DEGREES_TO_RADIANS, aimDirection.y * DEGREES_TO_RADIANS );

	m_possessedEntity->SetLocalRotation( glm::vec3( m_possessedEntity->GetLocalRotation().x, ( targetRotation * RADIANS_TO_DEGREES ) - 180.0f, m_possessedEntity->GetLocalRotation().z ) );

	std::shared_ptr< PhysicsComponent > playerPhysicsComponent = std::static_pointer_cast< PhysicsComponent >( m_possessedEntity->GetComponent( ComponentType::c_PHYSICS ) );
	playerPhysicsComponent->physics_body->SetTransform( playerPhysicsComponent->physics_body->GetPosition(), -targetRotation );
}
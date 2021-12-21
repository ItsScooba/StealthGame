#include "PhysicsSystem.h"

#include "Engine.h"

#include "EventEntitySpawned.h"
#include "EventEntityDestroyed.h"

#include <math.h>











PhysicsSystem::PhysicsSystem() : I_System( SystemType::s_PHYSICS )
{

}




PhysicsSystem::~PhysicsSystem()
{

}




//Initialize the Physics System.
bool PhysicsSystem::Initialize()
{
	EventListener entitySpawnListener = fastdelegate::MakeDelegate( this, &PhysicsSystem::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &PhysicsSystem::OnEntityDestroyed );

	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnListener );
	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );

	return true;
}




//Cleanup and shutdown the Physics System.
void PhysicsSystem::Shutdown()
{
	EventListener entitySpawnListener = fastdelegate::MakeDelegate( this, &PhysicsSystem::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &PhysicsSystem::OnEntityDestroyed );

	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnListener );
	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );
}




//Update the physics system.
void PhysicsSystem::Update( const float& deltaTime )
{
	//Remove any bodies scheduled for removal from the game world.
	while ( !m_bodiesScheduledForRemoval.empty() ) {
		Engine::GetInstance().GetGameScene()->GetWorld().physics_simulation->DestroyBody( m_bodiesScheduledForRemoval.front()->physics_body );
		m_bodiesScheduledForRemoval.erase( m_bodiesScheduledForRemoval.begin() );
	}

	//Loop through each physics body and update it.
	for ( std::shared_ptr< PhysicsComponent > body : m_physicsBodies ) {
		b2Vec2 bodyPosition = body->physics_body->GetPosition();

		//Check for a parent position, since we are setting each game object's local position.
		if( body->parent_entity->GetParentObject() != NULL ) {
			glm::vec3 parentWorldPosition = body->parent_entity->GetParentObject()->GetWorldPosition();
			bodyPosition -= b2Vec2( parentWorldPosition.x, parentWorldPosition.z );
		}

		body->parent_entity->SetLocalPosition( glm::vec3( bodyPosition.x, body->parent_entity->GetLocalPosition().y, bodyPosition.y ) );
		//body->parent_entity->SetLocalRotation( glm::vec3( body->parent_entity->GetLocalRotation().x, 
		//	body->physics_body->GetAngle() * RADIANS_TO_DEGREES, body->parent_entity->GetLocalRotation().z ) );
	}
}




//Event Handler for when a new entity is created and spawned.
void PhysicsSystem::OnEntitySpawned( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntitySpawned > spawnEvent = std::static_pointer_cast< EventEntitySpawned >( gameEvent );

	std::shared_ptr< PhysicsComponent > entityPhysicsComponent = std::static_pointer_cast< PhysicsComponent >( spawnEvent->entity_spawned->GetComponent( ComponentType::c_PHYSICS ) );
	if ( entityPhysicsComponent == nullptr ) return;

	//Initialize the physics body's position to match that of the entity.
	glm::vec3 entityWorldPosition = spawnEvent->entity_spawned->GetWorldPosition();
	entityPhysicsComponent->physics_body->SetTransform( b2Vec2( entityWorldPosition.x, entityWorldPosition.z ), 0.0f );

	m_physicsBodies.push_back( entityPhysicsComponent );
}




//Event fired when an entity is destroyed and removed from the game world.
void PhysicsSystem::OnEntityDestroyed( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntityDestroyed > destroyedEvent = std::static_pointer_cast< EventEntityDestroyed >( gameEvent );

	for ( std::vector< std::shared_ptr< PhysicsComponent > >::iterator physicsIter = m_physicsBodies.begin(); physicsIter != m_physicsBodies.end(); physicsIter++ ) {
		if ( physicsIter->get()->parent_entity == destroyedEvent->entity_destroyed ) {
			m_bodiesScheduledForRemoval.push_back( *physicsIter );
			m_physicsBodies.erase( physicsIter );
			break;
		}
	}
}
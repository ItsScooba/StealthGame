#include "AI_System.h"

#include "Engine.h"

#include "EventEntitySpawned.h"
#include "EventEntityDestroyed.h"
















AI_System::AI_System() : I_System( SystemType::s_AI )
{

}




AI_System::~AI_System()
{

}




//Initialize the AI System.
bool AI_System::Initialize()
{
	EventListener entitySpawnListener = fastdelegate::MakeDelegate( this, &AI_System::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &AI_System::OnEntityDestroyed );

	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnListener );
	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );

	return true;
}




//Shutdown and cleanup the AI System.
void AI_System::Shutdown()
{
	EventListener entitySpawnListener = fastdelegate::MakeDelegate( this, &AI_System::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &AI_System::OnEntityDestroyed );

	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnListener );
	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );
}




//Update the AI_System.
void AI_System::Update( const float& deltaTime )
{
	//Update each AI Components' controller.
	for( std::shared_ptr< AI_Component > aiComponent : m_aiComponents ) {
		aiComponent->ai_controller->Tick();
	}
}




//Event handler for when an object is spawned into the game world.
void AI_System::OnEntitySpawned( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntitySpawned > spawnEvent = std::static_pointer_cast< EventEntitySpawned >( gameEvent );
	std::shared_ptr< AI_Component > objectAI = std::static_pointer_cast< AI_Component >( spawnEvent->entity_spawned->GetComponent( ComponentType::c_AI ) );
	if( objectAI != NULL ) {
		m_aiComponents.push_back( objectAI );
	}
}




//Event handler for when an entity is destroyed and removed from the game world.
void AI_System::OnEntityDestroyed( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntityDestroyed > destroyedEvent = std::static_pointer_cast< EventEntityDestroyed >( gameEvent );

	std::shared_ptr< AI_Component > objectAI = std::static_pointer_cast< AI_Component >( destroyedEvent->entity_destroyed->GetComponent( ComponentType::c_AI ) );
	if( objectAI != NULL ) {
		for( std::vector< std::shared_ptr< AI_Component > >::iterator aiIter = m_aiComponents.begin(); aiIter != m_aiComponents.end(); aiIter++ ) {
			if( *aiIter == objectAI ) {
				m_aiComponents.erase( aiIter );
				break;
			}
		}
	}
}
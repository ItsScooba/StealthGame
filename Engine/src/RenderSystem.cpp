#include "RenderSystem.h"



#include "Engine.h"

#include <glm\gtc\matrix_transform.hpp>

#include "EventEntitySpawned.h"
#include "EventEntityDestroyed.h"











RenderSystem::RenderSystem() : I_System( SystemType::s_RENDERING )
{

}




RenderSystem::~RenderSystem()
{

}




bool RenderSystem::Initialize()
{
	EventListener entitySpawnEventListener = fastdelegate::MakeDelegate( this, &RenderSystem::AddEntity );
	EventListener entityDestroyedEventListener = fastdelegate::MakeDelegate( this, &RenderSystem::RemoveEntity );

	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnEventListener );
	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedEventListener );

	return true;
}




void RenderSystem::Shutdown()
{
	EventListener entitySpawnEventListener = fastdelegate::MakeDelegate( this, &RenderSystem::AddEntity );
	EventListener entityDestroyedEventListener = fastdelegate::MakeDelegate( this, &RenderSystem::RemoveEntity );

	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnEventListener );
	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedEventListener );
}




void RenderSystem::AddEntity( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntitySpawned > entitySpawnEvent = std::static_pointer_cast< EventEntitySpawned >( gameEvent );

	std::shared_ptr< RenderComponent > entityRenderComponent = std::static_pointer_cast< RenderComponent >( entitySpawnEvent->entity_spawned->GetComponent( ComponentType::c_RENDERABLE ) );
	if ( entityRenderComponent == nullptr ) return;

	//Build the render data's model transformation matrix initially, and add the data to the renderer.
	entitySpawnEvent->entity_spawned->BuildWorldTransform();
	m_dynamicRenderComponents.push_back( std::shared_ptr< RenderComponent >( entityRenderComponent ) );
}




void RenderSystem::RemoveEntity( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntityDestroyed > entityDestroyedEvent = std::static_pointer_cast< EventEntityDestroyed >( gameEvent );

	std::shared_ptr< RenderComponent > entityRenderComponent = std::static_pointer_cast< RenderComponent >( entityDestroyedEvent->entity_destroyed->GetComponent( ComponentType::c_RENDERABLE ) );
	if ( entityRenderComponent == nullptr ) return;

	for ( std::vector< std::shared_ptr< RenderComponent > >::iterator iter = m_dynamicRenderComponents.begin();  
		iter != m_dynamicRenderComponents.end(); iter++ ) {
		
		if ( *iter == entityRenderComponent ) {
			m_dynamicRenderComponents.erase( iter );
			break;
		}
	}
}




void RenderSystem::Update( const float& deltaTime )
{
	std::vector< std::shared_ptr< Mesh > > sceneMeshData;
	for ( auto dynamicMeshIterator : m_dynamicRenderComponents ) {
		dynamicMeshIterator->parent_entity->BuildWorldTransform();
		dynamicMeshIterator->render_resource->SetTransform( dynamicMeshIterator->parent_entity->GetWorldTransform() );
		sceneMeshData.push_back( dynamicMeshIterator->render_resource );
	}

	Engine::GetInstance().GetRenderer().SetSceneMeshData( sceneMeshData );
}
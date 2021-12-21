#include "AnimationSystem.h"

#include "Engine.h"

#include "EventEntitySpawned.h"
#include "EventEntityDestroyed.h"

#include "RenderComponent.h"







AnimationSystem::AnimationSystem() : I_System( SystemType::s_ANIMATION )
{
}




AnimationSystem::~AnimationSystem()
{

}




//Initialize the Animation System.
bool AnimationSystem::Initialize()
{
	EventListener entitySpawnedListener = fastdelegate::MakeDelegate( this, &AnimationSystem::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &AnimationSystem::OnEntityDestroyed );

	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnedListener );
	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );

	return true;
}




//Shutdown the Animation System.
void AnimationSystem::Shutdown()
{
	EventListener entitySpawnedListener = fastdelegate::MakeDelegate( this, &AnimationSystem::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &AnimationSystem::OnEntityDestroyed );

	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnedListener );
	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );


}




//Update the Animation System.
void AnimationSystem::Update( const float& deltaTime )
{
	//Update any active animations.
	for ( std::shared_ptr< AnimationComponent > animationComponent : m_animationComponents ) {

		if ( animationComponent->GetActiveAnimation() != NULL ) {

			std::shared_ptr< RenderComponent > objectRenderComponent = std::static_pointer_cast< RenderComponent >
				( animationComponent->parent_entity->GetComponent( ComponentType::c_RENDERABLE ) );

			animationComponent->GetActiveAnimation()->Tick();

			//If the animation has advanced, update any child objects' transforms to match the socket's transform.
			if ( animationComponent->GetActiveAnimation() != NULL && animationComponent->GetActiveAnimation()->IsPoseDirty() ) {
				animationComponent->skeletal_data.ApplyPose( animationComponent->GetActiveAnimation()->GetCurrentPose() );
				animationComponent->GetActiveAnimation()->SetPoseDirtyFalse();

				//Apply any material parameters for the pose to the object's mesh.
				for( std::shared_ptr< BaseMaterialParameter > materialParameter
					: animationComponent->GetActiveAnimation()->GetCurrentPose()->material_parameters ) {
					objectRenderComponent->render_resource->GetMaterial()->AddMaterialParameter( materialParameter->parameter_id, materialParameter );
				}

				//Apply new transform to child objects.
				std::vector< std::shared_ptr< Socket > >::const_iterator socketTransformIter = animationComponent->skeletal_data.GetSockets().begin();
				while ( socketTransformIter != animationComponent->skeletal_data.GetSockets().end() ) {
					const std::vector< std::shared_ptr< GameObject > >& childObjects = animationComponent->parent_entity->GetChildren();

					//Apply socket transforms to the object's children meshes for this pose.
					for ( std::shared_ptr< GameObject > child : childObjects ) {
						if ( child->GetAttachedSocketName() == socketTransformIter->get()->socket_name ) {
							child->SetLocalPosition( socketTransformIter->get()->socket_position );
							child->SetLocalRotation( socketTransformIter->get()->socket_rotation );
						}
					}

					socketTransformIter++;
				}
			}

			//If the animation stopped and is no longer active, revert back to the idle base pose.
			else if ( animationComponent->GetActiveAnimation()->GetCurrentPose() == NULL ) {
				animationComponent->skeletal_data.ApplyPose( animationComponent->GetBasePose() );
				animationComponent->StopPlayingAnimation();

				//Apply any material parameters for the pose to the object's mesh.
				for( std::shared_ptr< BaseMaterialParameter > materialParameter
					: animationComponent->GetBasePose()->material_parameters ) {
					objectRenderComponent->render_resource->GetMaterial()->AddMaterialParameter( materialParameter->parameter_id, materialParameter );
				}

				//Apply new transform to child objects.
				std::vector< std::shared_ptr< Socket > >::const_iterator socketTransformIter = animationComponent->skeletal_data.GetSockets().begin();
				while ( socketTransformIter != animationComponent->skeletal_data.GetSockets().end() ) {
					const std::vector< std::shared_ptr< GameObject > >& childObjects = animationComponent->parent_entity->GetChildren();
					for ( std::shared_ptr< GameObject > child : childObjects ) {
						if ( child->GetAttachedSocketName() == socketTransformIter->get()->socket_name ) {
							child->SetLocalPosition( socketTransformIter->get()->socket_position );
							child->SetLocalRotation( socketTransformIter->get()->socket_rotation );
						}
					}

					socketTransformIter++;
				}

			}
		}
	}
}




//Event Handler for when an entity is spawned.
void AnimationSystem::OnEntitySpawned( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntitySpawned > spawnEvent = std::static_pointer_cast< EventEntitySpawned >( gameEvent );
	
	//Check if the spawned entity has an animation component.
	std::shared_ptr< AnimationComponent > animationComponent = std::static_pointer_cast< AnimationComponent >( spawnEvent->entity_spawned->GetComponent( ComponentType::c_ANIMATION ) );
	if ( animationComponent == nullptr ) return;

	m_animationComponents.push_back( animationComponent );

}




//Event Handler for when an entity is destroyed.
void AnimationSystem::OnEntityDestroyed( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntityDestroyed > destroyEvent = std::static_pointer_cast< EventEntityDestroyed >( gameEvent );

	std::shared_ptr< AnimationComponent > animationComponent = std::static_pointer_cast< AnimationComponent >( destroyEvent->entity_destroyed->GetComponent( ComponentType::c_ANIMATION ) );
	if ( animationComponent == nullptr ) 
		return;

	for ( std::vector< std::shared_ptr< AnimationComponent > >::iterator animIter = m_animationComponents.begin(); animIter != m_animationComponents.end(); animIter++ ) {
		if ( animIter->get()->parent_entity == destroyEvent->entity_destroyed ) {
			m_animationComponents.erase( animIter );
			break;
		}
	}
}
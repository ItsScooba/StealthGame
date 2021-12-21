#include "WeaponsSystem.h"



#include "Engine.h"

#include "EventEntitySpawned.h"
#include "EventEntityDestroyed.h"

#include "EventDamage.h"

#include "RenderComponent.h"
#include "HealthComponent.h"








WeaponsSystem::WeaponsSystem() : I_System( SystemType::s_WEAPONS )
{

}




WeaponsSystem::~WeaponsSystem()
{
}




bool WeaponsSystem::Initialize()
{
	EventListener entitySpawnedListener = fastdelegate::MakeDelegate( this, &WeaponsSystem::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &WeaponsSystem::OnEntityDestroyed );
	EventListener damageEventListener = fastdelegate::MakeDelegate( this, &WeaponsSystem::OnDamageTaken );

	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnedListener );
	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );
	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::DAMAGE, damageEventListener );

	return true;
}




void WeaponsSystem::Shutdown()
{
	EventListener entitySpawnedListener = fastdelegate::MakeDelegate( this, &WeaponsSystem::OnEntitySpawned );
	EventListener entityDestroyedListener = fastdelegate::MakeDelegate( this, &WeaponsSystem::OnEntityDestroyed );
	EventListener damageEventListener = fastdelegate::MakeDelegate( this, &WeaponsSystem::OnDamageTaken );

	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_SPAWNED, entitySpawnedListener );
	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::ENTITY_DESTROYED, entityDestroyedListener );
	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::DAMAGE, damageEventListener );

}




void WeaponsSystem::Update( const float& deltaTime )
{
	//Update any active or recently active fire modes.
	for( std::shared_ptr< WeaponComponent > weaponComponent : m_weaponComponents ) {
		weaponComponent->fire_mode->Tick( deltaTime );
	}

	//Update any active hit markers.
	std::map< std::shared_ptr< GameObject >, float >::iterator hitMarkerIter = m_activeHitMarkers.begin();
	while( !m_activeHitMarkers.empty() && hitMarkerIter != m_activeHitMarkers.end() ) {
		hitMarkerIter->second -= deltaTime;
		if( hitMarkerIter->second <= 0.0f ) {
			std::shared_ptr< RenderComponent > hitObjectRenderComp = std::static_pointer_cast< RenderComponent >( hitMarkerIter->first->GetComponent( ComponentType::c_RENDERABLE ) );
			hitObjectRenderComp->render_resource->GetMaterial()->AddMaterialParameter( "materialColor",
				std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor",
					hitObjectRenderComp->render_resource->GetMaterial()->GetBaseColor()[0], hitObjectRenderComp->render_resource->GetMaterial()->GetBaseColor()[1],
					hitObjectRenderComp->render_resource->GetMaterial()->GetBaseColor()[2], hitObjectRenderComp->render_resource->GetMaterial()->GetBaseColor()[3] ) ) );
			m_activeHitMarkers.erase( hitMarkerIter );
		}
		else 
			hitMarkerIter++;
	}
}




void WeaponsSystem::OnEntitySpawned( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntitySpawned > spawnEvent = std::static_pointer_cast< EventEntitySpawned >( gameEvent );
	std::shared_ptr< WeaponComponent > entityWeaponComponent = std::static_pointer_cast< WeaponComponent >( spawnEvent->entity_spawned->GetComponent( ComponentType::c_WEAPON ) );
	if( entityWeaponComponent == NULL ) 
		return;

	m_weaponComponents.push_back( entityWeaponComponent );
}




void WeaponsSystem::OnEntityDestroyed( std::shared_ptr< I_Event > gameEvent )
{
	std::shared_ptr< EventEntityDestroyed > destroyedEvent = std::static_pointer_cast< EventEntityDestroyed >( gameEvent );
	std::shared_ptr< WeaponComponent > entityWeaponComponent = std::static_pointer_cast< WeaponComponent >( destroyedEvent->entity_destroyed->GetComponent( ComponentType::c_WEAPON ) );
	if( entityWeaponComponent == NULL )
		return;

	for( std::vector< std::shared_ptr< WeaponComponent > >::iterator weaponComponent = m_weaponComponents.begin(); 
		weaponComponent != m_weaponComponents.end(); weaponComponent++ ) {
		if( *weaponComponent == entityWeaponComponent ) {
			m_weaponComponents.erase( weaponComponent );
			break;
		}
	}
}




//Event handler called when a game object takes damage.
void WeaponsSystem::OnDamageTaken( std::shared_ptr< I_Event > gameEvent )
{
	static const float hit_marker_duration = 0.4f;
	static const glm::vec4 hit_marker_color = glm::vec4( 0.9f, 0.9f, 0.9f, 1.0f );
	std::shared_ptr< EventDamage > damageEvent = std::static_pointer_cast< EventDamage >( gameEvent );


	//Update the objects' health.
	std::shared_ptr< HealthComponent > objectHealth = std::static_pointer_cast< HealthComponent >( damageEvent->object_hit->GetComponent( ComponentType::c_HEALTH ) );
	objectHealth->SetCurrentHealth( objectHealth->GetCurrentHealth() - damageEvent->total_damage );
	
	//If the object is out of health, destroy it.
	if( objectHealth->GetCurrentHealth() <= 0 ) {
		Engine::GetInstance().GetEventDispatcher().FireEvent( std::shared_ptr< EventEntityDestroyed >( new EventEntityDestroyed( damageEvent->object_hit ) ) );
	}
	
	//Display a hit marker on the object.
	std::shared_ptr< RenderComponent > hitObjectRenderComp = std::static_pointer_cast< RenderComponent >( damageEvent->object_hit->GetComponent( ComponentType::c_RENDERABLE ) );
	hitObjectRenderComp->render_resource->GetMaterial()->AddMaterialParameter( "materialColor",
		std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor", hit_marker_color.r, hit_marker_color.g, hit_marker_color.b, hit_marker_color.a ) ) );


	m_activeHitMarkers.emplace( damageEvent->object_hit, hit_marker_duration );
}
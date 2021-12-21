#include "SingleShotFireMode.h"

#include "Engine.h"

#include "WeaponComponent.h"

#include "EventDamage.h"

















SingleShotFireMode::SingleShotFireMode( std::shared_ptr< WeaponComponent > parentWeapon )
	: FireMode( parentWeapon )
{
}




SingleShotFireMode::~SingleShotFireMode()
{
}




void SingleShotFireMode::BeginFire( const float& fireCooldownDuration )
{
	glm::vec3 weaponWorldPosition = m_parentWeapon->parent_entity->GetWorldPosition();
	b2Vec2 mousePosition( Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCursor()->GetPositionX(),
		Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCursor()->GetPositionY() );
	b2Vec2 mouseWorldPosition = mousePosition + b2Vec2( Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCamera().GetPosition().x, 
		Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCamera().GetPosition().y );

	//Calculate the position to fire from and the direction.
	b2Vec2 startPoint( weaponWorldPosition.x, weaponWorldPosition.z );
	
	//Create a ray cast representing this shot being fired.
	std::shared_ptr< RayCastResults > hitResults = Engine::GetInstance().GetGameScene()->GetWorld().RayCast( startPoint, mouseWorldPosition );
	if( hitResults->GetClosestHit() != NULL )
		HandleHit( hitResults->GetClosestHit() );
}




void SingleShotFireMode::EndFire()
{

}




void SingleShotFireMode::Tick( const float& deltaTime )
{

}




void SingleShotFireMode::HandleHit( std::shared_ptr< GameObject > objectHit )
{
	Engine::GetInstance().GetEventDispatcher().FireEvent( std::shared_ptr< EventDamage >( new EventDamage( objectHit, 40 ) ) );
}
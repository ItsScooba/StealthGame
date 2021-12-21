#include "FireMode.h"

#include "SDL2\SDL.h"
#include "Engine.h"

#include "WeaponComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

#include "FixtureUserData.h"

#include "EventDamage.h"

















FireMode::FireMode( std::shared_ptr< WeaponComponent > parentWeapon )
	: m_parentWeapon( parentWeapon ), m_currentSwingTimeRemaining( 0.0f )
{
}




FireMode::~FireMode()
{

}




//Handle actions to take when beginning to fire this weapon, whether it's a swing or shooting a gun.
void FireMode::BeginFire( const float& fireCooldownDuration )
{
	//Create the fixture to represent this fire modes' swing collision shape.
	float fixtureAngle = 0.0f;
	const glm::vec3& weaponDimensions( m_parentWeapon->parent_entity->GetDimensions() );
	b2CircleShape swordSwingShape;
	swordSwingShape.m_p = b2Vec2( 0.0f, m_parentWeapon->parent_entity->GetLocalPosition().z );
	swordSwingShape.m_radius = m_parentWeapon->parent_entity->GetDimensions().z / 1.5f;

	FixtureUserData* fixtureUserData = new FixtureUserData( m_parentWeapon->parent_entity );
	fixtureUserData->SetContactBeginCallback( fastdelegate::MakeDelegate( this, &FireMode::HandleHit ) );


	b2FixtureDef meleeSwingCollisionDef;
	meleeSwingCollisionDef.shape = &swordSwingShape;
	meleeSwingCollisionDef.userData = fixtureUserData;
	meleeSwingCollisionDef.filter.categoryBits = PhysicsComponent::BodyCategory::WEAPON;

	std::shared_ptr< PhysicsComponent > weaponParentPhysicsBody = std::static_pointer_cast< PhysicsComponent >
		( m_parentWeapon->parent_entity->GetParentObject()->GetComponent( ComponentType::c_PHYSICS ) );
	b2Fixture* attackFixture = weaponParentPhysicsBody->physics_body->CreateFixture( &meleeSwingCollisionDef );

	m_parentWeapon->m_isFiring = true;
	m_parentWeapon->m_hasAttackBeenReleased = false;
	m_currentSwingTimeRemaining = fireCooldownDuration;
}




//Handle actions to take when an attack is finishing, and clean up for the next attack.
void FireMode::EndFire()
{	
	m_parentWeapon->m_hasAttackBeenReleased = true;
}




//Handle when an object is hit with this weapon's fire mode.
void FireMode::HandleHit( std::shared_ptr< GameObject > objectHit )
{
	Engine::GetInstance().GetEventDispatcher().FireEvent( std::shared_ptr< EventDamage >( new EventDamage( objectHit, -1 ) ) );
}




//Update the fire mode if it is firing or recently fired.
void FireMode::Tick( const float& deltaTime )
{
	//Check if the weapon is firing.
	if( !m_parentWeapon->m_isFiring ) 
		return;

	//Otherwise, first update the timer for the swing. Check if the swing has ended.
	m_currentSwingTimeRemaining -= deltaTime;
	if( m_currentSwingTimeRemaining <= 0.0f )
		OnMeleeSwingEnd();

}




//Check whether the weapon can currently fire.
bool FireMode::CanFire()
{
	//Check if the weapon is already firing.
	if( m_parentWeapon->m_isFiring )
		return false;
	if( !m_parentWeapon->m_hasAttackBeenReleased )
		return false;
	if( m_currentSwingTimeRemaining > 0.0f )
		return false;

	return true;
}




//Melee specific function for cleaning up the behavior used to initiate melee attack and physics to check for collisions.
void FireMode::OnMeleeSwingEnd()
{
	std::shared_ptr< PhysicsComponent > weaponParentPhysicsBody = std::static_pointer_cast< PhysicsComponent >
		( m_parentWeapon->parent_entity->GetParentObject()->GetComponent( ComponentType::c_PHYSICS ) );

	//Find the weapon attack collision fixture.
	for( b2Fixture* fixture = weaponParentPhysicsBody->physics_body->GetFixtureList(); fixture; fixture = fixture->GetNext() ) {

		std::shared_ptr< GameObject > fixtureParentObject = ( ( FixtureUserData* ) fixture->GetUserData() )->parent_game_object;
		if( fixtureParentObject == m_parentWeapon->parent_entity ) {
			weaponParentPhysicsBody->physics_body->DestroyFixture( fixture );
			break;
		}
	}


	m_parentWeapon->m_isFiring = false;
}
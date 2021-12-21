#include "PhysicsContactListener.h"

#include "GameObject.h"

#include "PhysicsComponent.h"
#include "FixtureUserData.h"










void PhysicsContactListener::PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{
	if( contact->GetFixtureA()->GetFilterData().categoryBits == PhysicsComponent::BodyCategory::WEAPON
		|| contact->GetFixtureB()->GetFilterData().categoryBits == PhysicsComponent::BodyCategory::WEAPON )
		contact->SetEnabled( false );
}




void PhysicsContactListener::BeginContact( b2Contact* contact )
{
	FixtureUserData* parentFixtureA = (FixtureUserData*) contact->GetFixtureA()->GetUserData();
	FixtureUserData* parentFixtureB = (FixtureUserData*) contact->GetFixtureB()->GetUserData();

	//Call any collision callback functions on each object, passing the other object it collided with.
	if( parentFixtureA != NULL )
		parentFixtureA->OnContactBegin( parentFixtureB->parent_game_object );
	if( parentFixtureB != NULL )
		parentFixtureB->OnContactBegin( parentFixtureA->parent_game_object );

}




void PhysicsContactListener::EndContact( b2Contact* contact )
{
	FixtureUserData* parentFixtureA = ( FixtureUserData* ) contact->GetFixtureA()->GetUserData();
	FixtureUserData* parentFixtureB = ( FixtureUserData* ) contact->GetFixtureB()->GetUserData();

	//Call any collision callback functions on each object, passing the other object it collided with.
	if( parentFixtureA != NULL )
		parentFixtureA->OnContactEnd( parentFixtureB->parent_game_object );
	if( parentFixtureB != NULL )
		parentFixtureB->OnContactEnd( parentFixtureA->parent_game_object );
}
#include "RayCastResults.h"

#include "FixtureUserData.h"


















RayCastResults::RayCastResults()
{

}




RayCastResults::~RayCastResults()
{

}




std::shared_ptr< GameObject > RayCastResults::GetClosestHit()
{
	if( m_rayCastIntersections.empty() )
		return NULL;
	else
		return m_rayCastIntersections.begin()->second;
}




float32 RayCastResults::ReportFixture( b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction )
{
	FixtureUserData* fixtureUserData = ( FixtureUserData* ) fixture->GetUserData();
	std::shared_ptr< GameObject > objectHit = fixtureUserData->parent_game_object;

	m_rayCastIntersections.emplace( fraction, objectHit );
	
	//Return 1 for the ray cast to get all intersections, return FRACTION to only get the first ( closest ) intersection.
	return 1.0f;
}
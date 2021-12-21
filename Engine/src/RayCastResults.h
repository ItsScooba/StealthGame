#pragma once








#include "Box2D\Box2D.h"

#include "glm\glm.hpp"

#include <memory>
#include <map>

#include "GameObject.h"

















class RayCastResults : public b2RayCastCallback
{
public:


	RayCastResults();
	~RayCastResults();


	std::shared_ptr< GameObject > GetClosestHit();

	float32 ReportFixture( b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction );


private:


	std::map< float, std::shared_ptr< GameObject > > m_rayCastIntersections;

};
#pragma once



#include "Box2D\Box2D.h"









//Class which handles when two bodies collide in the physics simulation.
class PhysicsContactListener : public b2ContactListener
{
public:


	void PreSolve( b2Contact* contact, const b2Manifold* oldManifold );

	void BeginContact( b2Contact* contact );
	void EndContact( b2Contact* contact );


};
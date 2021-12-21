#pragma once



#include "Component.h"

#include <vector>
#include <math.h>

#include "Box2D\Box2D.h"



#define DEGREES_TO_RADIANS ( M_PI / 180.0f )
#define RADIANS_TO_DEGREES ( 180.0f / M_PI )


//Component used to give an entity a physical body in the world.
class PhysicsComponent : public Component
{
public:

	static enum BodyCategory {
		DEFAULT = 0x0001,
		WEAPON = 0x0002
	};

public:


	PhysicsComponent( std::shared_ptr< GameObject > ownerEntity, b2Body* physicsBody )
		: Component( ComponentType::c_PHYSICS, ownerEntity ), physics_body( physicsBody )
	{
	}

	~PhysicsComponent()
	{}
	

public:


	b2Body* physics_body;
	

};
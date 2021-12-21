#pragma once



#include <vector>
#include <memory>

#include "Box2D\Box2D.h"

#include "I_System.h"

#include "PhysicsComponent.h"







class PhysicsSystem : public I_System
{
public:


	PhysicsSystem();
	~PhysicsSystem();

	bool Initialize();
	void Shutdown();

	void Update( const float& deltaTime );


private:


	void OnEntitySpawned( std::shared_ptr< I_Event > spawnEvent );
	void OnEntityDestroyed( std::shared_ptr< I_Event > destroyEvent );


private:


	std::vector< std::shared_ptr< PhysicsComponent > > m_physicsBodies;
	std::vector< std::shared_ptr< PhysicsComponent > > m_bodiesScheduledForRemoval;


};
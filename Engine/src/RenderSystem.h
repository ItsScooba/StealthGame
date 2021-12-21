#pragma once








#include "I_System.h"

#include <memory>
#include <vector>

#include "RenderComponent.h"





class RenderSystem : public I_System
{
public:


	RenderSystem();
	~RenderSystem();

	bool Initialize();
	void Shutdown();
	
	void Update( const float& deltaTime );


private:


	void AddEntity( std::shared_ptr< I_Event > entitySpawnedEvent );
	void RemoveEntity( std::shared_ptr< I_Event > entityDestroyedEvent );


private:


	std::vector< std::shared_ptr< RenderComponent > > m_dynamicRenderComponents;


};
#pragma once



#include "I_System.h"

#include <vector>

#include "AnimationComponent.h"







//System that manages animations.
class AnimationSystem : public I_System
{
public:


	AnimationSystem();
	~AnimationSystem();

	bool Initialize();
	void Shutdown();

	void Update( const float& deltaTime );


private:


	void OnEntitySpawned( std::shared_ptr< I_Event > gameEvent );
	void OnEntityDestroyed( std::shared_ptr< I_Event > gameEvent );


private:


	std::vector< std::shared_ptr< AnimationComponent > > m_animationComponents;


};
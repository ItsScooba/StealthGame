#pragma once



#include <memory>

#include "GameObject.h"














//Class used for creeating game objects in a specific way.
class ActorFactory
{
public:


	ActorFactory();
	~ActorFactory();

	static std::shared_ptr< GameObject > CreatePlayerActor();
	static std::shared_ptr< GameObject > CreateMonsterActor();
	static std::shared_ptr< GameObject > CreateWeaponObject();


};
#pragma once








#include "I_Event.h"

#include "GameObject.h"


//Event fired whenever a new entity is spawned into the game world.
class EventEntitySpawned : public I_Event
{
public:


	EventEntitySpawned( std::shared_ptr< GameObject > entityObjectSpawned ) : I_Event( EventType::ENTITY_SPAWNED ), entity_spawned( entityObjectSpawned )
	{}

	
public:


	std::shared_ptr< GameObject > entity_spawned;

};
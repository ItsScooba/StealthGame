#pragma once








#include "I_Event.h"

#include "GameObject.h"


//Event fired whenever an entity is destroyed completely.
class EventEntityDestroyed : public I_Event
{
public:


	EventEntityDestroyed( std::shared_ptr< GameObject > entityObjectDestroyed ) : I_Event( EventType::ENTITY_DESTROYED ), entity_destroyed( entityObjectDestroyed )
	{}


public:


	std::shared_ptr< GameObject > entity_destroyed;
};
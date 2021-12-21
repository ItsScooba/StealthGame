#pragma once



#include <memory>









enum EventType
{
	DAMAGE,
	ENTITY_SPAWNED,
	ENTITY_DESTROYED,
	POST_RENDER
};




struct I_Event
{

	I_Event( EventType eventType ) : event_type( eventType )
	{}
	
	virtual ~I_Event() {};


public:

	const EventType event_type;

};
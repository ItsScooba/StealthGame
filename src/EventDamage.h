#pragma once








#include <memory>

#include "GameObject.h"




#include "I_Event.h"




class EventDamage : public I_Event
{
public:


	EventDamage( std::shared_ptr< GameObject > objectHit, int damageAmount )
		: I_Event( EventType::DAMAGE ), object_hit( objectHit ), total_damage( damageAmount )
	{}
	

public:


	const std::shared_ptr< GameObject > object_hit;
	const int total_damage;


};
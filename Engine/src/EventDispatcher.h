#pragma once


#include <map>
#include <vector>

#include "FastDelegate\FastDelegate.h"
#include "I_Event.h"


typedef fastdelegate::FastDelegate1< std::shared_ptr< I_Event > > EventListener;




class EventDispatcher
{
public:


	EventDispatcher();
	~EventDispatcher();

	void RegisterEventListener( EventType eventType, EventListener eventListener );
	void UnregisterEventListener( EventType eventType, EventListener& eventListenerDelegate );

	void FireEvent( I_Event* gameEvent );
	void FireEvent( std::shared_ptr< I_Event > gameEvent );


private:


	std::map< EventType, std::vector< EventListener > > m_eventHandlers;

};
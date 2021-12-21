#include "EventDispatcher.h"













EventDispatcher::EventDispatcher()
{

}




EventDispatcher::~EventDispatcher()
{

}




void EventDispatcher::RegisterEventListener( EventType eventType, EventListener listener )
{
	//See if there are any existing event listeners for this event type first.
	std::map< EventType, std::vector< EventListener > >::iterator handlerTypeIter = m_eventHandlers.find( eventType );
	if ( handlerTypeIter == m_eventHandlers.end() ) {
		std::vector< EventListener > newListenerList;
		newListenerList.push_back( listener );
		m_eventHandlers.emplace( eventType, newListenerList );
	}
	else
		handlerTypeIter->second.push_back( listener );
}




//Pass in the same delegate used to register the event listener, and find it by comparing memory addresses.
void EventDispatcher::UnregisterEventListener( EventType eventType, EventListener& listenerDelegate )
{
	std::map< EventType, std::vector< EventListener > >::iterator mapIter = m_eventHandlers.find( eventType );
	if ( mapIter != m_eventHandlers.end() ) {
		for ( std::vector< EventListener >::iterator listenerIter = mapIter->second.begin(); 
		listenerIter != mapIter->second.end(); listenerIter++ ) {
			if ( *listenerIter == listenerDelegate ) {
				mapIter->second.erase( listenerIter );
				return;
			}
		}
	}
}




void EventDispatcher::FireEvent( I_Event* gameEvent )
{
	//Find any handlers registered for this type of event.
	std::map< EventType, std::vector< EventListener > >::iterator mapIter = m_eventHandlers.find( gameEvent->event_type );
	if ( mapIter != m_eventHandlers.end() ) {
		std::shared_ptr< I_Event > theEvent( gameEvent );
		for ( EventListener handler : mapIter->second ) {
			handler( theEvent );
		}
	}
}




void EventDispatcher::FireEvent( std::shared_ptr< I_Event > gameEvent )
{
	//Find any handlers registered for this type of event.
	std::map< EventType, std::vector< EventListener > >::iterator mapIter = m_eventHandlers.find( gameEvent->event_type );
	if ( mapIter != m_eventHandlers.end() ) {
		for ( EventListener handler : mapIter->second ) {
			handler( gameEvent );
		}
	}
}
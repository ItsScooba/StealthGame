#include "InputManager.h"

#include "KeyboardHandler.h"
#include "MouseHandler.h"












InputManager::InputManager()
{

}




InputManager::~InputManager()
{

}




bool InputManager::Initialize()
{
	if ( !InitRawInputHandler( new KeyboardHandler() ) ) return false;
	if ( !InitRawInputHandler( new MouseHandler() ) ) return false;

	return true;
}




void InputManager::Shutdown()
{
}




bool InputManager::HandleEvent( const SDL_Event& e )
{
	//Declare an empty Input Event pointer that will be filled if the event is handled.
	InputEvent inputEventContainer;

	//Check each raw input handler if it can handle the event.
	for ( std::shared_ptr< RawInputHandler > rawInputHandler : m_rawInputHandlers ) {
		if ( rawInputHandler->HandleInput( e, inputEventContainer ) ) {
			m_processedRawInputQueue.push_back( inputEventContainer );
			return true;
		}
	}

	return false;
}




//Initialize a raw input handler for mapping raw hardware input into actions the game understands.
bool InputManager::InitRawInputHandler( RawInputHandler* rawInputHandler )
{
	if ( !rawInputHandler->LoadInputMap() )
		return false;
	m_rawInputHandlers.push_back( std::shared_ptr< RawInputHandler >( rawInputHandler ) );
	return true;
}
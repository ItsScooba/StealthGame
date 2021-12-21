#include "MouseHandler.h"













MouseHandler::MouseHandler()
{
}




MouseHandler::~MouseHandler()
{
}




//Load any mapped inputs from a file ( eventually ) and store them for translating hardware input.
bool MouseHandler::LoadInputMap()
{
	m_mouseMap.emplace( SDL_BUTTON_LEFT, "Attack" );
	m_mouseMap.emplace( SDL_BUTTON_RIGHT, "Block" );
	return true;
}




//Try handling an input event passed to the mouse handler. Returns success.
bool MouseHandler::HandleInput( const SDL_Event& inputEvent, InputEvent& translatedInputEvent )
{
	//Make sure the event is the correct type.
	if ( inputEvent.syswm.type == SDL_MOUSEBUTTONDOWN || inputEvent.syswm.type == SDL_MOUSEBUTTONUP ) {

		//Definitely a keyboard event, try to find if anything is bound to this key.
		std::map< Uint8, std::string >::iterator buttonMapping = m_mouseMap.find( inputEvent.button.button );
		if ( buttonMapping == m_mouseMap.end() )
			return false;
		else {

			translatedInputEvent.input_action = buttonMapping->second;
			translatedInputEvent.input_state = inputEvent.button.state;
			return true;
		}
	}
}
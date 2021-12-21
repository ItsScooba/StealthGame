#include "KeyboardHandler.h"













KeyboardHandler::KeyboardHandler()
{
}




KeyboardHandler::~KeyboardHandler()
{
}




//Load any mapped inputs from a file ( eventually ) and store them for translating hardware input.
bool KeyboardHandler::LoadInputMap()
{

	m_keyboardMap.emplace( SDL_SCANCODE_W, "MovePlayerForward" );
	m_keyboardMap.emplace( SDL_SCANCODE_S, "MovePlayerBackward" );
	m_keyboardMap.emplace( SDL_SCANCODE_D, "MovePlayerRight" );
	m_keyboardMap.emplace( SDL_SCANCODE_A, "MovePlayerLeft" );

	m_keyboardMap.emplace( SDL_SCANCODE_LSHIFT, "Sprint" );

	return true;
}




//Try handling an input event passed to the keyboard handler. Returns success.
bool KeyboardHandler::HandleInput( const SDL_Event& inputEvent, InputEvent& translatedInputEvent )
{
	//Make sure the event is the correct type.
	if ( inputEvent.syswm.type == SDL_KEYDOWN || inputEvent.syswm.type == SDL_KEYUP ) {
		
		//Definitely a keyboard event, try to find if anything is bound to this key.
		std::map< SDL_Scancode, std::string >::iterator keyMapping = m_keyboardMap.find( inputEvent.key.keysym.scancode );
		if ( keyMapping == m_keyboardMap.end() )
			return false;
		else {

			translatedInputEvent.input_action = keyMapping->second;
			translatedInputEvent.input_state = inputEvent.key.state;
			return true;
		}
	}

	return false;
}
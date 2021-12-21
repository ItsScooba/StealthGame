#pragma once



#include "RawInputHandler.h"

#include <SDL2\SDL.h>

#include <map>
#include <string>






//Class used for translating raw keyboard input into game commands.
class KeyboardHandler : public RawInputHandler
{
public:


	KeyboardHandler();
	~KeyboardHandler();

	bool LoadInputMap();
	bool HandleInput( const SDL_Event& inputEvent, InputEvent& translatedInputEvent );


private:


	std::map< SDL_Scancode, std::string > m_keyboardMap;

};
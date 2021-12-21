#pragma once



#include "RawInputHandler.h"

#include <SDL2\SDL.h>

#include <map>
#include <string>







//Class used to translate raw mouse input into game commands.
class MouseHandler : public RawInputHandler
{
public:


	MouseHandler();
	~MouseHandler();

	bool LoadInputMap();
	bool HandleInput( const SDL_Event& inputEvent, InputEvent& translatedInputEvent );


private:


	std::map< Uint8, std::string > m_mouseMap;	//0 == LEFT, 1 == MIDDLE, 2 == RIGHT

};
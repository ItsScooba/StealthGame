#pragma once



#include "SDL2\SDL.h"

#include "InputManager.h"







class RawInputHandler
{
public:

	
	virtual ~RawInputHandler() {};

	virtual bool LoadInputMap() = 0;
	virtual bool HandleInput( const SDL_Event& inputEvent, InputEvent& translatedInputEvent ) = 0;
	
};
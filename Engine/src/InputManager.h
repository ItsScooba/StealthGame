#pragma once

#include <SDL2\SDL.h>

#include <memory>
#include <vector>





//Forward Declares.
class RawInputHandler;









//Struct used to hold data about an input event that has occured.
struct InputEvent
{
	std::string input_action;
	Uint8 input_state;
	
};




class InputManager
{
public:


	InputManager();
	~InputManager();

	bool Initialize();
	void Shutdown();

	bool HandleEvent( const SDL_Event& e );


private:


	bool InitRawInputHandler( RawInputHandler* rawInputHandler );


private:


	std::vector< std::shared_ptr< RawInputHandler > > m_rawInputHandlers;
	std::vector< InputEvent > m_processedRawInputQueue;


public:


	std::vector< InputEvent >& GetInputQueue() { return m_processedRawInputQueue; }

};
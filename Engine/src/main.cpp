#include "Window.h"

#include "Engine.h"







//Main function for any program.
int main( int argc, char** argv )
{
	//Initialize the engine.
	if ( !Engine::GetInstance().Initialize() ) 
		return -1;

	//Run the engines' main loop.
	Engine::GetInstance().Run();

	//Shutdown the game engine when the main game loop exits.
	Engine::GetInstance().Shutdown();
	
	//Return 0 to represent success.
	return 0;
}
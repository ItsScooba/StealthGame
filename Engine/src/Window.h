#pragma once

#include <memory>

#include <SDL2\SDL.h>




class Window
{
public:


	Window();
	~Window();

	bool Load( int pixelWidth, int pixelHeight );
	void Destroy();

	void SwapBuffers();														//Swaps the back buffer with the front buffer, displaying everything drawn in the last render pass.


private:


	int m_screenWidth, m_screenHeight;

	SDL_Window* m_window;
	SDL_GLContext m_renderContext;
	

public:


	const int& GetScreenWidth() { return m_screenWidth; }
	const int& GetScreenHeight() { return m_screenHeight; }

};
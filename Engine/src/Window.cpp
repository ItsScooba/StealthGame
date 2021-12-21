#include "Window.h"

#include "Engine.h"
#include "ResourceManager.h"

#include "Mesh.h"
#include "Material.h"
#include "Sprite.h"






Window::Window()
{
	m_screenWidth = m_screenHeight = -1;
}




Window::~Window()
{

}




bool Window::Load( int pixelWidth, int pixelHeight )
{
	m_screenWidth = pixelWidth;
	m_screenHeight = pixelHeight;

	//Create the window itself.
	m_window = SDL_CreateWindow( "Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pixelWidth, pixelHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	m_renderContext = SDL_GL_CreateContext( m_window );

	//Hide the cursor.
	SDL_ShowCursor( 0 );

	if ( !ResourceManager::GetInstance().LoadFont( "arialbd" ) ) return false;



	return true;
} 




void Window::Destroy()
{
	SDL_GL_DeleteContext( m_renderContext );
	SDL_DestroyWindow( m_window );
}




//Render the current display.
void Window::SwapBuffers()
{
	SDL_GL_SwapWindow( m_window );

}
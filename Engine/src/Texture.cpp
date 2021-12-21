#include "Texture.h"

#include "SOIL\SOIL.h"








Texture::Texture() : m_textureID( -1 ), m_width( -1.0f ), m_height( -1.0f )
{
	glGenTextures( 1, &m_textureID );
}




Texture::~Texture()
{
	glDeleteTextures( 1, &m_textureID );
}




bool Texture::LoadImage( const std::string& textureName )
{
	int textureWidth = 0, textureHeight = 0;

	std::string filePath = "../Content/" + textureName + ".png";

	//Use SOIL to load the texture, then assign it to a OpenGL Texture2D.
	unsigned char* image = SOIL_load_image( filePath.c_str(), &textureWidth, &textureHeight, 0, SOIL_LOAD_RGBA );
	m_width = ( float ) textureWidth;
	m_height = ( float ) textureHeight;

	//Generate the texture.
	glBindTexture( GL_TEXTURE_2D, m_textureID );

	//Give the texture to OpenGL.
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	//Make sure the texture loaded corrently.
	if ( m_textureID == -1 ) return false;

	//Set the texture not to repeat or clamp to edges of the window.
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );		//Set the filtering to linear.
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );		//Set the filtering to linear.

	return true;
}




void Texture::Unload()
{
}
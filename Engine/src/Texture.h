#pragma once


#include <string>
#include <vector>

#include <gl\glew.h>






//Class used to represent a loaded texture into memory.
class Texture
{
public:


	Texture();
	~Texture();

	virtual bool LoadImage( const std::string& textureName );
	void Unload();


protected:


	GLuint m_textureID;
	float m_width, m_height;


public:


	const GLuint& GetTextureID() { return m_textureID; }

};
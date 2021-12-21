#pragma once


#include <string>
#include <vector>
#include <memory>

#include <gl\glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H




//POD Struct for each character represented in the font. MUST GO BEFORE FONT TO PREVENT ERRORS, NO FORWARD DECLARES.
struct Character
{
	float bearingX, bearingY;
	float width, height;
	float textureCoordinates[8];
	float xAdvance;

};





//Actual font class used to render text.
class Font
{
public:


	Font();
	~Font();

	bool Load( const std::string& filePath );
	void Unload();
	void GenerateStringVertexData( std::string string, float xCursorPosition, float yCursorPosition, std::vector< float >& vertexCoordinateBuffer, std::vector< float >& textureCoordinateBuffer );


private:


	Character m_characters[ 128 ];
	GLuint m_textureAtlasID;
	float m_lineHeight;


public:

	const GLuint& GetTextureAtlasID() { return m_textureAtlasID; }


};








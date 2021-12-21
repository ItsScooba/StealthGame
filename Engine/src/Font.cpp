#include "Font.h"

#include <fstream>
#include <sstream>

#include "Texture.h"







Font::Font()
{
	m_lineHeight = -1.0f;
	m_textureAtlasID = -1;
}




Font::~Font()
{

}




bool Font::Load( const std::string& filePath )
{
	//Initialize FreeType library.
	FT_Library library;
	int error = 0;
	error = FT_Init_FreeType( &library );
	if ( error )
		return false;

	FT_Face fontFace;
	error = FT_New_Face( library, filePath.c_str(), 0, &fontFace );
	if ( error )
		return false;

	//Set the font size. ( 0 width will set based on height );
	FT_Set_Pixel_Sizes( fontFace, 0, 16 );

	//Generate a texture atlas that contains all of the individual glyphs for this font.
	glGenTextures( 1, &m_textureAtlasID );
	glBindTexture( GL_TEXTURE_2D, m_textureAtlasID );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	//Generate rendering data for each character in the font, using 128 basic ASCII glyphs.
	float textureWidth = 0, textureHeight = 0;
	for ( int i = 0; i < 128; i++ ) {
		
		//Load the glyph for this character.
		if ( FT_Load_Char( fontFace, i, FT_LOAD_RENDER ) )
			continue;
		
		//Figure out the total texture width and height required to store all the letters.
		textureWidth += fontFace->glyph->bitmap.width;
		if ( fontFace->glyph->bitmap.rows > textureHeight )
			textureHeight = fontFace->glyph->bitmap.rows;


	}

	//Generate the texture with the texture atlas data.
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, textureWidth, textureHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0 );

	//Now populate the texture atlas with the bitmaps.
	float xAtlasPos = 0;
	for ( int i = 0; i < 128; i++ ) {
	
		//Load the glyph for this character.
		if ( FT_Load_Char( fontFace, i, FT_LOAD_RENDER ) ) {
			m_characters[i].width = 0.0f;
			m_characters[i].height = 0.0f;
			m_characters[i].xAdvance = 0.0f;
			m_characters[i].bearingX = 0.0f; 
			m_characters[i].bearingY = 0.0f;


			m_characters[i].textureCoordinates[0] = 0.0f;		m_characters[i].textureCoordinates[1] = 0.0f;
			m_characters[i].textureCoordinates[2] = 0.0f;		m_characters[i].textureCoordinates[3] = 0.0f;
			m_characters[i].textureCoordinates[4] = 0.0f;		m_characters[i].textureCoordinates[5] = 0.0f;
			m_characters[i].textureCoordinates[6] = 0.0f;		m_characters[i].textureCoordinates[7] = 0.0f;
			continue;
		}

		m_characters[i].width = fontFace->glyph->bitmap.width;
		m_characters[i].height = fontFace->glyph->bitmap.rows;
		m_characters[i].bearingX = fontFace->glyph->bitmap_left;
		m_characters[i].bearingY = fontFace->glyph->bitmap_top;
		m_characters[i].xAdvance = ( fontFace->glyph->advance.x >> 6 );		//Bit shift value by 6 to get the value in pixels.

		m_characters[i].textureCoordinates[0] = xAtlasPos / textureWidth;											m_characters[i].textureCoordinates[1] = fontFace->glyph->bitmap.rows / textureHeight;
		m_characters[i].textureCoordinates[2] = ( xAtlasPos + fontFace->glyph->bitmap.width ) / textureWidth;		m_characters[i].textureCoordinates[3] = fontFace->glyph->bitmap.rows / textureHeight;
		m_characters[i].textureCoordinates[4] = ( xAtlasPos + fontFace->glyph->bitmap.width ) / textureWidth;		m_characters[i].textureCoordinates[5] = 0.0f;
		m_characters[i].textureCoordinates[6] = xAtlasPos / textureWidth;											m_characters[i].textureCoordinates[7] = 0.0f;

		glTexSubImage2D( GL_TEXTURE_2D, 0, xAtlasPos, 0, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer );
		xAtlasPos += fontFace->glyph->bitmap.width;
	}

	glBindTexture( GL_TEXTURE_2D, NULL );
	FT_Done_Face( fontFace );
	FT_Done_FreeType( library );

	return true;
}




void Font::Unload()
{
	glDeleteTextures( 1, &m_textureAtlasID );
}




void Font::GenerateStringVertexData( std::string string, float xCursorPos, float yCursorPos, std::vector< float >& vertexCoordinateBuffer, std::vector< float >& textureCoordinateBuffer )
{
	float currentCursorX = xCursorPos;
	float currentCursorY = yCursorPos;

	//Loop through each letter in the string.
	for ( std::string::iterator i = string.begin(); i != string.end(); i++ ) {
		int characterAscii = ( int ) *i;

		vertexCoordinateBuffer.push_back( currentCursorX );
		vertexCoordinateBuffer.push_back( currentCursorY );
		vertexCoordinateBuffer.push_back( 0.0f );
		
		vertexCoordinateBuffer.push_back( currentCursorX + m_characters[ characterAscii ].width );
		vertexCoordinateBuffer.push_back( currentCursorY );
		vertexCoordinateBuffer.push_back( 0.0f );

		vertexCoordinateBuffer.push_back( currentCursorX + m_characters[ characterAscii ].width );
		vertexCoordinateBuffer.push_back( currentCursorY + m_characters[ characterAscii ].height );
		vertexCoordinateBuffer.push_back( 0.0f );

		vertexCoordinateBuffer.push_back( currentCursorX + m_characters[ characterAscii ].width );
		vertexCoordinateBuffer.push_back( currentCursorY + m_characters[ characterAscii ].height );
		vertexCoordinateBuffer.push_back( 0.0f );

		vertexCoordinateBuffer.push_back( currentCursorX );
		vertexCoordinateBuffer.push_back( currentCursorY + m_characters[ characterAscii ].height );
		vertexCoordinateBuffer.push_back( 0.0f );

		vertexCoordinateBuffer.push_back( currentCursorX );
		vertexCoordinateBuffer.push_back( currentCursorY );
		vertexCoordinateBuffer.push_back( 0.0f );


		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 0 ] );		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 1 ] );
		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 2 ] );		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 3 ] );
		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 4 ] );		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 5 ] );
		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 4 ] );		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 5 ] );
		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 6 ] );		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 7 ] );
		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 0 ] );		textureCoordinateBuffer.push_back( m_characters[ characterAscii ].textureCoordinates[ 1 ] );

		currentCursorX += m_characters[ characterAscii ].xAdvance;
	}
}
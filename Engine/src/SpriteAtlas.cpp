#include "SpriteAtlas.h"

#include <tinyxml2.h>











SpriteAtlas::SpriteAtlas() : Texture()
{
}




SpriteAtlas::~SpriteAtlas()
{
}




//Load the sprite atlas and all of it's frame data.
bool SpriteAtlas::LoadImage( const std::string& spriteAtlasTextureID )
{
	if ( !Texture::LoadImage( spriteAtlasTextureID ) ) return false;

	//Parse any frame data for each of the frames on the sprite atlas.
	if ( !LoadAtlasFrameCoordinates( "Textures/TextureAtlasData/" + spriteAtlasTextureID ) )
		return false;	
	return true;
}




bool SpriteAtlas::LoadAtlasFrameCoordinates( const std::string& textureName )
{
	//The XML Document reference.
	std::string fullFileName = "../Content/" + textureName + ".xml";
	tinyxml2::XMLDocument xmlFile;
	if ( xmlFile.LoadFile( fullFileName.c_str() ) != 0 ) {
		xmlFile.Clear();
		return false;
	}

	//Get the root element. ( TextureAtlas )
	tinyxml2::XMLElement* rootElement = xmlFile.RootElement();
	if ( rootElement == NULL ) {
		xmlFile.Clear();
		return false;
	}


	//Get frame data for each frame Backwards because of how data is generated.
	for ( tinyxml2::XMLElement* element = rootElement->LastChildElement(); element != NULL; element = element->PreviousSiblingElement() ) {

		//Variables to hold data.
		float frameWidth = -1.0f, frameHeight = -1.0f;
		float framePosX = -1.0f, framePosY = -1.0f;

		//Get height attribute.
		const char* attributeName = element->Attribute( "h" );
		if ( attributeName == NULL ) return false;
		else element->QueryFloatAttribute( "h", &frameHeight );

		//Get Width attribute.
		attributeName = element->Attribute( "w" );
		if ( attributeName == NULL ) return false;
		else element->QueryFloatAttribute( "w", &frameWidth );

		//Get Y-Coordinate.
		attributeName = element->Attribute( "y" );
		if ( attributeName == NULL ) return false;
		else element->QueryFloatAttribute( "y", &framePosY );

		//Get x-coordinate.
		attributeName = element->Attribute( "x" );
		if ( attributeName == NULL ) return false;
		else element->QueryFloatAttribute( "x", &framePosX );



		//Now calculate the UV coords normalized.
		float x1 = framePosX / m_width;
		float y1 = framePosY / m_height;
		float x2 = ( framePosX + frameWidth ) / m_width;
		float y2 = ( framePosY + frameHeight ) / m_height;

		std::vector< float > frameData = { x1, y1, x2, y1, x2, y2, x2, y2, x1, y2, x1, y1 };
		m_textureAtlasFrames.push_back( frameData );

	}


	//Clear the XML file when done.
	xmlFile.Clear();
	return true;
}




const std::vector< float >& SpriteAtlas::GetTextureAtlasCoordinates( int textureAtlasFrameIndex )
{
	if ( textureAtlasFrameIndex >= m_textureAtlasFrames.size() ) {
		std::vector< float > emptyVector;
		return emptyVector;
	}

	else
		return m_textureAtlasFrames.at( textureAtlasFrameIndex );
}
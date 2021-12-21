#pragma once



#include "Texture.h"

#include <vector>









//Subclass of texture used for sprite sheets, or a sprite atlas. Holds texture coordinates of each individual frame on the atlas.
class SpriteAtlas : public Texture
{
public:


	SpriteAtlas();
	~SpriteAtlas();

	bool LoadImage( const std::string& spriteAtlasFileName );

	const std::vector< float >& GetTextureAtlasCoordinates( int textureAtlasFrameIndex );


private:


	bool LoadAtlasFrameCoordinates( const std::string& spriteAtlasFileName );


private:


	std::vector< std::vector< float > > m_textureAtlasFrames;


};
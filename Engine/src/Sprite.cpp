#include "Sprite.h"

#include "Engine.h"











Sprite::Sprite( std::shared_ptr< Texture > spriteTexture ) : Mesh(), m_isBillboard( false )
{
	SetTexture( spriteTexture );
}




Sprite::~Sprite()
{

}




void Sprite::SetAsQuad( float width, float height )
{
	std::vector< float > vertexData = {
		0.0f, 0.0f, 0.0f,
		width, 0.0f, 0.0f,
		width, height, 0.0f,
		width, height, 0.0f,
		0.0f, height, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	SetVertexData( vertexData );
}




void Sprite::SetTexture( std::shared_ptr< Texture > texture )
{
	std::vector< float > textureCoordinates = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	GetMaterial()->AddMaterialParameter( "activeTexture", std::shared_ptr< TextureParameter >( new TextureParameter( "activeTexture", texture ) ) );
	BindVertexAttribute( "textureCoordinates", textureCoordinates, 2 );
}




//Calculate and return the modelview transformation matrix used for rendering.
glm::mat4 Sprite::GetModelViewRenderMatrix( const glm::mat4& viewMatrix )
{
	glm::mat4 modelView = viewMatrix * m_modelTransformMatrix;
	for ( int x = 0; x < 3; x++ ) {
		for ( int y = 0; y < 3; y++ ) {
			if ( x == y ) modelView[x][y] = 1.0f;
			else		  modelView[x][y] = 0.0f;
		}
	}

	return modelView;
}
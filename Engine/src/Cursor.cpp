#include "Cursor.h"

#include "Engine.h"
#include "ResourceManager.h"
#include "DefaultSpriteMaterial.h"









Cursor::Cursor() : GUI_Widget( "Cursor" ), m_mesh( new Mesh( std::shared_ptr< DefaultSpriteMaterial >( new DefaultSpriteMaterial() ) ) ), m_cursorPositionX( 0 ), m_cursorPositionY( 0 )
{
	std::vector< float > meshVertices = {
		0.0f, 0.0f, 0.0f,
		16.0f, 0.0f, 0.0f,
		16.0f, 16.0f, 0.0f,
		0.0f, 16.0f, 0.0f,
	};


	std::vector< int > indexData = {
		0, 1, 2, 2, 3, 0
	};

	m_mesh->SetVertexData( meshVertices );
	m_mesh->SetIndexData( indexData );
}




Cursor::~Cursor()
{

}




void Cursor::Tick()
{
	SDL_GetMouseState( &m_cursorPositionX, &m_cursorPositionY );
	m_cursorPositionY = Engine::GetInstance().GetApplicationWindow().GetScreenHeight() - m_cursorPositionY;
	
	m_mesh->SetTransform( glm::translate( glm::mat4( 1.0f ), glm::vec3( m_cursorPositionX, m_cursorPositionY, 0.0f ) ) );
}




bool Cursor::SetTexture( std::string textureID )
{
	if ( !ResourceManager::GetInstance().LoadTexture( textureID ) ) return false;

	m_mesh->GetMaterial()->AddMaterialParameter( "activeTexture", std::shared_ptr< TextureParameter >
		( new TextureParameter( "activeTexture", ResourceManager::GetInstance().GetTexture( textureID ) ) ) );

	std::vector< float > textureCoordinates = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};

	m_mesh->BindVertexAttribute( "textureCoordinates", textureCoordinates, 2 );


	return true;
}




void Cursor::OnDraw()
{
	Engine::GetInstance().GetRenderer().DrawMesh( m_mesh );
}
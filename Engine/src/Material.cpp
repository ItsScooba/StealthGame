#include "Material.h"

#include <vector>

#include "Engine.h"
#include "ResourceManager.h"
#include "Texture.h"





Material::Material() : m_vertexArrayObject( -1 ), m_baseColor( 0.0f, 0.0f, 0.0f, 0.0f )
{
	//Set the proper shader.
	m_materialShader = ResourceManager::GetInstance().GetShader( "DefaultShader" );

	//Generate the vertex array object used to pass data to the shaders.
	glGenVertexArrays( 1, &m_vertexArrayObject );

	Initialize();
}




Material::Material( std::shared_ptr< Shader > materialShaderProgram )
	: m_materialShader( materialShaderProgram ), m_vertexArrayObject( -1 ), m_baseColor( 0.0f, 0.0f, 0.0f, 0.0f )
{

	//Generate the vertex array object used to pass data to the shaders.
	glGenVertexArrays( 1, &m_vertexArrayObject );

	Initialize();
}




Material::~Material()
{
	if ( m_vertexArrayObject != -1 )
		glDeleteVertexArrays( 1, &m_vertexArrayObject );
}




//Load the initial state of the material and prepare it for rendering.
bool Material::Initialize()
{
	m_materialParameters.emplace( "materialColor", std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor", m_baseColor[0], m_baseColor[1], m_baseColor[2], m_baseColor[3] ) ) );

	return true;
}




void Material::SetBaseMaterialColor( float r, float g, float b, float a )
{
	m_baseColor = glm::vec4( r, g, b, a );
}




void Material::AddMaterialParameter( std::string parameterName, std::shared_ptr< BaseMaterialParameter > parameter )
{
	std::map< std::string, std::shared_ptr< BaseMaterialParameter > >::iterator parameterIter = m_materialParameters.find( parameterName );
	if ( parameterIter != m_materialParameters.end() ) {
		m_materialParameters.erase( parameterIter );
	}

	m_materialParameters.emplace( parameterName, parameter );
}




void Material::SetUniform( std::string uniformID, const glm::mat4& matrix )
{
	glUniformMatrix4fv( glGetUniformLocation( m_materialShader->GetProgramID(), uniformID.c_str() ), 1, GL_FALSE, &matrix[0][0] );
}




//Bind any per instance data for a draw call to the shader.
void Material::BindInstanceParameters()
{
	m_materialShader->UseProgram();
	glBindVertexArray( m_vertexArrayObject );

	for ( std::map< std::string, std::shared_ptr< BaseMaterialParameter > >::iterator parameterIter = m_materialParameters.begin(); 
	parameterIter != m_materialParameters.end(); parameterIter++ ) {
		parameterIter->second->Bind( m_materialShader->GetProgramID() );
	}

}
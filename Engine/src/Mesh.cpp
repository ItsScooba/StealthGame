#include "Mesh.h"

#include "ResourceManager.h"
#include <glm\gtc\matrix_transform.hpp>
#include "Engine.h"










VertexAttribute::VertexAttribute( const std::vector< float >& attributeData, std::string vertexAttributeID, int numElementsPerVertex )
	: attributeID( vertexAttributeID ), elementsPerVertex( numElementsPerVertex )
{
	glGenBuffers( 1, &VBO_ID );
	glBindBuffer( GL_ARRAY_BUFFER, VBO_ID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * attributeData.size(), &attributeData[0], GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, NULL );
}




VertexAttribute::~VertexAttribute()
{
	glDeleteBuffers( 1, &VBO_ID );
}









Mesh::Mesh() : m_numberOfVertices( 0 ), m_modelTransformMatrix( glm::mat4( 1.0f ) )
{
	m_material.reset( new Material() );
}




Mesh::Mesh( std::shared_ptr< Material > material )
	: m_numberOfVertices( 0 ), m_material( material ), m_modelTransformMatrix( glm::mat4( 1.0f ) )
{

}




Mesh::~Mesh()
{
}




void Mesh::SetVertexData( const std::vector< float >& vertexData )
{
	m_numberOfVertices = vertexData.size() / 3;
	BindVertexAttribute( "vertexPosition", vertexData, 3 );
}




void Mesh::SetIndexData( const std::vector< int >& indexData )
{
	glGenBuffers( 1, &m_indexBufferObject );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject );
	

	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * indexData.size(), &indexData[0], GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );

	m_numberOfVertices = indexData.size();
}




void Mesh::SetMaterial( std::shared_ptr< Material > material )
{
	m_material = material;
	glBindVertexArray( m_material->GetVertexArrayObject() );

	for ( std::shared_ptr< VertexAttribute > vertexAttribute : m_vertexAttributes ) {
		
		GLuint attributeIndex = glGetAttribLocation( m_material->GetShaderProgram()->GetProgramID(), vertexAttribute->attributeID.c_str() );
		if ( attributeIndex == -1 )
			return;

		glBindBuffer( GL_ARRAY_BUFFER, vertexAttribute->VBO_ID );
		glEnableVertexArrayAttrib( m_material->GetVertexArrayObject(), attributeIndex );
		glVertexAttribPointer( attributeIndex, vertexAttribute->elementsPerVertex, GL_FLOAT, GL_FALSE, 0, 0 );
	}

	glBindVertexArray( NULL );
}




void Mesh::BindVertexAttribute( std::string vertexAttributeID, const std::vector< float >& vertexAttributeData, int numElementsPerVertex )
{
	//Vertex Attribute for this data, currently nullptr.
	std::shared_ptr< VertexAttribute > vertexAttribute( nullptr );

	//Get the OpenGL attribute index inside the shader program.
	GLuint attributeIndex = glGetAttribLocation( m_material->GetShaderProgram()->GetProgramID(), vertexAttributeID.c_str() );
	if ( attributeIndex == -1 )
		return;

	//First, check to see if this vertex attribute already exists.
	for ( std::shared_ptr< VertexAttribute > existingVertexAttribute : m_vertexAttributes ) {
		if ( existingVertexAttribute->attributeID == vertexAttributeID ) {
			vertexAttribute = existingVertexAttribute;
			break;
		}
	}

	//If vertex attribute is still nullptr, one with that ID doesn't exist yet, so create it.
	if ( vertexAttribute == nullptr ) {
		vertexAttribute.reset( new VertexAttribute( vertexAttributeData, vertexAttributeID, numElementsPerVertex ) );
		m_vertexAttributes.push_back( vertexAttribute );
		glBindVertexArray( m_material->GetVertexArrayObject() );
		glEnableVertexArrayAttrib( m_material->GetVertexArrayObject(), attributeIndex );
		glBindBuffer( GL_ARRAY_BUFFER, vertexAttribute->VBO_ID );
		glVertexAttribPointer( attributeIndex, vertexAttribute->elementsPerVertex, GL_FLOAT, GL_FALSE, 0, 0 );
		glBindVertexArray( NULL );

	}

	//Bind the vertex array object.
	glBindBuffer( GL_ARRAY_BUFFER, vertexAttribute->VBO_ID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * vertexAttributeData.size(), &vertexAttributeData[0], GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, NULL );

}




void Mesh::SetTransform( glm::mat4 newTransformMatrix )
{
	m_modelTransformMatrix = newTransformMatrix;
}




//Calculate and return the model view transform used when rendering this mesh.
glm::mat4 Mesh::GetModelViewRenderMatrix( const glm::mat4& viewMatrix )
{
	return viewMatrix * m_modelTransformMatrix;
}
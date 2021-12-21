#pragma once


#include <memory>
#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <string>

#include "Material.h"









//Struct to hold data about a specific vertex attribute for a mesh.
struct VertexAttribute
{
	VertexAttribute( const std::vector< float >& attributeData, std::string attributeID, int dataElementsPerVertex );
	~VertexAttribute();

	const std::string attributeID;
	int elementsPerVertex;
	GLuint VBO_ID;
};







class Mesh
{
public:


	Mesh();
	Mesh( std::shared_ptr< Material > material );
	virtual ~Mesh();

	void SetMaterial( std::shared_ptr< Material > material );
	void SetVertexData( const std::vector< float >& vertexData );
	void SetIndexData( const std::vector< int >& indexData );

	void BindVertexAttribute( std::string vertexAttributeID, const std::vector< float >& vertexAttributeData, int elementsPerVertex );
	void SetTransform( glm::mat4 newTransform );
	virtual glm::mat4 GetModelViewRenderMatrix( const glm::mat4& viewMatrix );


protected:


	int m_numberOfVertices;

	std::shared_ptr< Material > m_material;
	std::vector< std::shared_ptr< VertexAttribute > > m_vertexAttributes;

	glm::mat4 m_modelTransformMatrix;

	GLuint m_indexBufferObject;


public:


	const std::shared_ptr< Material > GetMaterial() { return m_material; }
	const int& GetNumVertices() { return m_numberOfVertices; }
	const glm::mat4& GetModelTransform() { return m_modelTransformMatrix; }

	const GLuint& GetIndexBufferObject() { return m_indexBufferObject; }

};
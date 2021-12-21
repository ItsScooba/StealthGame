#pragma once

#include <memory>
#include <map>
#include <string>
#include <glm\gtc\matrix_transform.hpp>

#include "Shader.h"
#include "MaterialParameters.h"

















class Material
{
public:


	Material();
	Material( std::shared_ptr< Shader > materialShaderProgram );
	virtual ~Material();

	virtual bool Initialize();

	void SetBaseMaterialColor( float r, float g, float b, float a );
	void AddMaterialParameter( std::string parameterName, std::shared_ptr< BaseMaterialParameter > materialParameter );
	void SetUniform( std::string uniformID, const glm::mat4& matrix );

	virtual void BindInstanceParameters();


protected:


	glm::vec4 m_baseColor;

	GLuint m_vertexArrayObject;
	std::shared_ptr< Shader > m_materialShader;
	std::map< std::string, std::shared_ptr< BaseMaterialParameter > > m_materialParameters;


public:


	const GLuint& GetVertexArrayObject() { return m_vertexArrayObject; }
	const std::shared_ptr< Shader > GetShaderProgram() { return m_materialShader; }
	const glm::vec4& GetBaseColor() { return m_baseColor; }

};
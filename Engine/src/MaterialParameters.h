#pragma once



#include <string>
#include <memory>
#include <glm\glm.hpp>
#include "GL\glew.h"


class Texture;








//Base class used to represent a generic uniform variable in the shader program used by materials.
struct BaseMaterialParameter
{
	BaseMaterialParameter( std::string parameterID )
		: parameter_id( parameterID )
	{};

	//Bind the parameter data to the uniform variable in the shader program.
	virtual bool Bind( const GLuint& materialShaderProgramID ) = 0;

public:

	const std::string parameter_id;
};









//Texture parameter. Binds a texture to sample from inside the shader program.
struct TextureParameter : public BaseMaterialParameter
{
	TextureParameter( std::string parameterID, std::shared_ptr< Texture > texture )
		: BaseMaterialParameter( parameterID ), texture_data( texture )
	{};

	bool Bind( const GLuint& materialShaderProgramID );

public:


	std::shared_ptr< Texture > texture_data;
};




//Bool parameter. Passes a true or false value to the shader uniform.
struct BoolParameter : public BaseMaterialParameter
{
	BoolParameter( std::string parameterID, bool boolValue = false )
		: BaseMaterialParameter( parameterID ), bool_data( boolValue )
	{};

	bool Bind( const GLuint& materialShaderProgramID );

public:


	bool bool_data;
};




//Scalar parameter. Passes a float uniform to the material shader.
struct ScalarParameter : public BaseMaterialParameter
{
	ScalarParameter( std::string parameterID, float scalarValue = 0.0f )
		: BaseMaterialParameter( parameterID ), scalar_data( scalarValue )
	{};

	bool Bind( const GLuint& materialShaderProgramID );

public:


	float scalar_data;
};




//Vector parameter. Uses a vector 4, but doesn't have to fill all 4 values ( for vector2, vector3, etc )
struct VectorParameter : public BaseMaterialParameter
{
	VectorParameter( std::string parameterID, float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f )
		: BaseMaterialParameter( parameterID ), vector_data( glm::vec4( x, y, z, w ) )
	{ };


	bool Bind( const GLuint& materialShaderProgramID );


public:

	
	glm::vec4 vector_data;
};
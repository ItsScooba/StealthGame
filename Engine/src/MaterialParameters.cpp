#include "MaterialParameters.h"

#include "Texture.h"











bool ScalarParameter::Bind( const GLuint& materialShaderProgramID )
{
	GLuint uniformLocation = glGetUniformLocation( materialShaderProgramID, parameter_id.c_str() );
	if ( uniformLocation == -1 )
		return false;
	glUniform1f( uniformLocation, scalar_data );
	return true;
}




bool VectorParameter::Bind( const GLuint& materialShaderProgramID )
{
	GLuint uniformLocation = glGetUniformLocation( materialShaderProgramID, parameter_id.c_str() );
	if ( uniformLocation == -1 )
		return false;
	glUniform4fv( uniformLocation, 1, &vector_data[0] );
	return true;
}




bool BoolParameter::Bind( const GLuint& materialShaderProgramID )
{
	GLuint uniformLocation = glGetUniformLocation( materialShaderProgramID, parameter_id.c_str() );
	if ( uniformLocation == -1 )
		return false;
	glUniform1i( uniformLocation, bool_data );
	return true;
}




bool TextureParameter::Bind( const GLuint& materialShaderProgramID )
{
	glBindTexture( GL_TEXTURE_2D, texture_data->GetTextureID() );
	return true;
}
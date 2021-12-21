#include "Shader.h"

#include <fstream>






Shader::Shader()
{
	m_shaderProgramID = NULL;
}




Shader::~Shader()
{
}




bool Shader::Load( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName )
{
	
	//Load in the individual shaders to use.
	GLuint vertexShaderID = ReadShaderFromFile( "../Content/GLSL_Shaders/" + vertexShaderFileName + ".vert", GL_VERTEX_SHADER );
	GLuint fragmentShaderID = ReadShaderFromFile( "../Content/GLSL_Shaders/" + fragmentShaderFileName + ".frag", GL_FRAGMENT_SHADER );
	if ( vertexShaderID == -1 || fragmentShaderID == -1 ) 
		return false;
	
	m_shaderProgramID = glCreateProgram();

	//Attach the shaders to the program.
	glAttachShader( m_shaderProgramID, vertexShaderID );
	glAttachShader( m_shaderProgramID, fragmentShaderID );
	glLinkProgram( m_shaderProgramID );

	//Check for any compile / build errors in the shaders.
	GLint success = GL_FALSE;
	glGetProgramiv( m_shaderProgramID, GL_LINK_STATUS, &success );
	if ( success != GL_TRUE ) {
		glDeleteProgram( m_shaderProgramID );
		m_shaderProgramID = NULL;
		return false;
	}

	glValidateProgram( m_shaderProgramID );
	glDeleteShader( vertexShaderID );
	glDeleteShader( fragmentShaderID );

	return true;
}




void Shader::Unload()
{
	glDeleteProgram( m_shaderProgramID );
	m_shaderProgramID = NULL;
}




GLuint Shader::ReadShaderFromFile( const std::string& shaderFileName, GLuint shaderType )
{
	//Open the file.
	GLuint shaderID = -1;
	std::ifstream sourceFile( shaderFileName.c_str() );

	//Make sure the file loaded corrently.
	if ( sourceFile ) {

		//Get the shader source code from the text file.
		std::string shaderString( ( std::istreambuf_iterator<char>( sourceFile ) ), std::istreambuf_iterator<char>() );

		//Create the shader ID.
		shaderID = glCreateShader( shaderType );

		//Set the shader source and compile.
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource( shaderID, 1, ( const GLchar** ) &shaderSource, NULL );
		glCompileShader( shaderID );

		//Make sure the shader compiled corrently.
		GLint status = GL_FALSE;
		glGetShaderiv( shaderID, GL_COMPILE_STATUS, &status );
		if ( status != GL_TRUE ) {
			glDeleteShader( shaderID );
			shaderID = -1;
		}
	}

	return shaderID;
}




void Shader::UseProgram()
{
	glUseProgram( m_shaderProgramID );
}




void Shader::StopUsingProgram()
{
	glUseProgram( NULL );
}
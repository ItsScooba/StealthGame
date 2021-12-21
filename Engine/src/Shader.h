#pragma once

#include <string>
#include <SDL2\SDL.h>
#include <gl\glew.h>


//Class used to load, unload, and manage a GLSL Shader program.
class Shader
{
public:


	Shader();
	~Shader();

	bool Load( const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName );
	void Unload();

	void UseProgram();
	void StopUsingProgram();


private:


	GLuint ReadShaderFromFile( const std::string& shaderFileName, GLuint shaderType );


private:


	GLuint m_shaderProgramID;


public:


	const GLuint& GetProgramID() { return m_shaderProgramID; }



};
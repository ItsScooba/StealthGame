#pragma once


#include <map>
#include <string>
#include <memory>






//Forward Declares
class Shader;
class Texture;
class Font;


//Singleton class used for managing all of the resources / assests needed.
class ResourceManager
{
public:


	~ResourceManager();

	bool LoadShader( std::string shaderID, std::string vertexShaderFileName, std::string fragmentShaderFileName );
	std::shared_ptr< Shader > GetShader( std::string shaderID );

	bool LoadTexture( std::string textureFileName );
	void UnloadTexture( std::string textureID );

	bool LoadTextureAtlas( std::string textureFileName );
	void UnloadTextureAtlas( std::string textureAtlasID );

	std::shared_ptr< Texture > GetTexture( std::string textureID );

	bool LoadFont( std::string fontName );
	std::shared_ptr< Font > GetFont( std::string fontID );

	void Shutdown();


private:


	ResourceManager();


private:

	
	std::map< std::string, std::shared_ptr< Shader > > m_loadedShaders;
	std::map< std::string, std::shared_ptr< Texture > > m_loadedTextures;
	std::map< std::string, std::shared_ptr< Font > > m_loadedFonts;

	//Singleton Global Accessor function.
public:

	static ResourceManager& GetInstance()
	{
		static ResourceManager resourceManager;
		return resourceManager;
	}




};
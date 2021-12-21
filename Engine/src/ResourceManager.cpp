#include "ResourceManager.h"

#include "Shader.h"
#include "Texture.h"
#include "Font.h"








ResourceManager::ResourceManager()
{
}




ResourceManager::~ResourceManager()
{
}




void ResourceManager::Shutdown()
{
	while ( !m_loadedFonts.empty() ) {
//		m_loadedFonts.begin()->second->Unload();
		m_loadedFonts.erase( m_loadedFonts.begin() );
	}

	while ( !m_loadedTextures.empty() ) {
		m_loadedTextures.begin()->second->Unload();
		m_loadedTextures.erase( m_loadedTextures.begin() );
	}

	while ( !m_loadedShaders.empty() ) {
		m_loadedShaders.begin()->second->Unload();
		m_loadedShaders.erase( m_loadedShaders.begin() );
	}
}




//Load a shader, and store it in the resource manager.
bool ResourceManager::LoadShader( std::string shaderName, std::string vertexShaderFileName, std::string fragmentShaderFileName )
{
	std::shared_ptr< Shader > shader( new Shader() );
	if ( !shader->Load( vertexShaderFileName, fragmentShaderFileName ) ) return false;
	m_loadedShaders.emplace( shaderName, std::shared_ptr< Shader >( shader ) );

	return true;
}




std::shared_ptr< Shader > ResourceManager::GetShader( std::string shaderID )
{
	std::map< std::string, std::shared_ptr< Shader > >::iterator shaderIter = m_loadedShaders.find( shaderID );
	if ( shaderIter != m_loadedShaders.end() )
		return shaderIter->second;
	else 
		return nullptr;
}




bool ResourceManager::LoadTexture( std::string textureFileName )
{
	std::shared_ptr< Texture > texture( new Texture() );
	if ( texture->LoadImage( "Textures/" + textureFileName ) ) {
		m_loadedTextures.emplace( textureFileName, texture );
		return true;
	}
	else
		return false;
}




void ResourceManager::UnloadTexture( std::string textureID )
{
	std::map < std::string, std::shared_ptr< Texture > >::iterator textureIter = m_loadedTextures.find( textureID );
	if ( textureIter != m_loadedTextures.end() ) {
		textureIter->second->Unload();
		m_loadedTextures.erase( textureIter );
	}
}




bool ResourceManager::LoadTextureAtlas( std::string textureFileName )
{
	std::shared_ptr< Texture > texture( new Texture() );
	if ( texture->LoadImage( "Textures/" + textureFileName )  ) {
		m_loadedTextures.emplace( textureFileName, texture );
		return true;
	}
	else
		return false;
}




void ResourceManager::UnloadTextureAtlas( std::string textureAtlasID )
{

}




std::shared_ptr< Texture > ResourceManager::GetTexture( std::string textureID )
{
	return m_loadedTextures.find( textureID )->second;
}




bool ResourceManager::LoadFont( std::string fontName )
{
	std::string fontPath = "../Content/Fonts/" + fontName + ".ttf";
	std::shared_ptr< Font > font( new Font() );
	if ( font->Load( fontPath ) ) {
		m_loadedFonts.emplace( fontName, font );
		return true;
	}
	else
		return false;
}




std::shared_ptr< Font > ResourceManager::GetFont( std::string fontID )
{
	return m_loadedFonts.find( fontID )->second;
}
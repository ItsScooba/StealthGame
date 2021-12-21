#include "DefaultSpriteMaterial.h"

#include "ResourceManager.h"













DefaultSpriteMaterial::DefaultSpriteMaterial() : Material( ResourceManager::GetInstance().GetShader( "DefaultSpriteShader" ) )
{
}




DefaultSpriteMaterial::~DefaultSpriteMaterial()
{
}




//Initialize the material to it's proper parameter and attribute state.
bool DefaultSpriteMaterial::Initialize()
{
	return true;
}




//Bind any per instance parameters for this material to use for rendering.
void DefaultSpriteMaterial::BindInstanceParameters()
{
	Material::BindInstanceParameters();

}
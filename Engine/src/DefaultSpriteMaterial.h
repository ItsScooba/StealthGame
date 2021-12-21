#pragma once








#include "Material.h"




//Material used by default when drawing sprites / 2D Texture mapped meshes.
class DefaultSpriteMaterial : public Material
{
public:


	DefaultSpriteMaterial();
	~DefaultSpriteMaterial();

	bool Initialize();
	void BindInstanceParameters();


private:




};
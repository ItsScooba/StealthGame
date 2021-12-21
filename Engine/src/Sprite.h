#pragma once

#include <memory>
#include <vector>

#include "Mesh.h"





class Sprite : public Mesh
{
public:



	Sprite( std::shared_ptr< Texture > spriteTexture );
	~Sprite();

	void SetAsQuad( float width, float height );
	void SetTexture( std::shared_ptr< Texture > texture );
	glm::mat4 GetModelViewRenderMatrix( const glm::mat4& viewMatrix );


private:


	bool m_isBillboard;


};
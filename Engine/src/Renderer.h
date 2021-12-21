#pragma once


#include <vector>
#include <memory>

#include <GL\glew.h>
#include <SDL2\SDL.h>

#include "GameObject.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"












//Class used to encapsulate OpenGL rendering functionality and data.
class Renderer
{
public:


	Renderer();
	~Renderer();

	bool Initialize();
	void Shutdown();

	void SetSceneMeshData( std::vector< std::shared_ptr< Mesh > > sceneViewMeshData );
	void RenderScene( Camera& sceneView );
	void DrawMesh( std::shared_ptr< Mesh > meshData );


private:


	bool GenerateScreenFramebuffer();
	void RenderFrameBufferToScreen();


private:


	std::shared_ptr< Texture > m_renderedSceneTextureBuffer;
	std::shared_ptr< Mesh > m_frameBufferMesh;
	GLuint m_sceneViewFrameBufferObject;
	
	std::vector< std::shared_ptr< Mesh > > m_currentSceneViewData;


};
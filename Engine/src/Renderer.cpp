#include "Renderer.h"

#include "Engine.h"
#include "ResourceManager.h"
#include "Shader.h"

#include "Material.h"
#include "Camera.h"

#include "PostRenderEvent.h"





Renderer::Renderer()
	: m_renderedSceneTextureBuffer( nullptr ), m_sceneViewFrameBufferObject( -1 )
{
}




Renderer::~Renderer()
{
}




bool Renderer::Initialize()
{
	//Initialize GLEW.
	glewExperimental = GL_TRUE;
	if ( glewInit() != GLEW_OK ) return false;

	//Create the rendering map to draw on.
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );

	//Enable depth testing and alpha blending.
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );
	
	//Set the default color and pixel depth to clear the map to when nothing is drawn.
	glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );		//Blue
	glClearDepth( 512.0f );


	if( !ResourceManager::GetInstance().LoadShader( "ScreenFrameBufferShader", "FramebufferScreenVertexShader", "FramebufferScreenFragmentShader" ) ) return false;
	if ( !GenerateScreenFramebuffer() ) return false;


	


	return true;
}




void Renderer::Shutdown()
{
	glDeleteFramebuffers( 1, &m_sceneViewFrameBufferObject );
}




void Renderer::SetSceneMeshData( std::vector< std::shared_ptr< Mesh > > sceneViewMeshData )
{
	m_currentSceneViewData = sceneViewMeshData;
}




//Alternate scene rendering where the renderer isn't collecting and storing the mesh data.
void Renderer::RenderScene( Camera& sceneView )
{
	//Bind the camera's Frame Buffer Object to render the scene to instead of the screen directly.
	glBindFramebuffer( GL_FRAMEBUFFER, m_sceneViewFrameBufferObject );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//Render the scene from the view supplied to the frame buffer object.
	for ( std::shared_ptr< Mesh > meshData : m_currentSceneViewData ) {
		meshData->GetMaterial()->BindInstanceParameters();
		glm::mat4 modelTransform = sceneView.GetProjectionMatrix() * meshData->GetModelViewRenderMatrix( sceneView.GetViewMatrix() );
		meshData->GetMaterial()->SetUniform( "transformationMatrix", modelTransform );
		glDrawArrays( GL_TRIANGLES, 0, meshData->GetNumVertices() );
	}

	//Unbind the frame buffer object, binding NULL renders back to the screen.
	glBindFramebuffer( GL_FRAMEBUFFER, NULL );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//Render the frame buffer texture to a quad for display on the screen.
	RenderFrameBufferToScreen();

	//Fire a Post Render Event after rendering the scene.
	Engine::GetInstance().GetEventDispatcher().FireEvent( new PostRenderEvent() );
}




//Generate the frame buffer used to render the final scene onto, then flip to display on the screen.
bool Renderer::GenerateScreenFramebuffer()
{
	//Generate the frame buffer object used to hold the rendered scene each frame before post processing effects are applied.
	glGenFramebuffers( 1, &m_sceneViewFrameBufferObject );
	glBindFramebuffer( GL_FRAMEBUFFER, m_sceneViewFrameBufferObject );

	//Generate the image used for the render target when rendering the scene and fill it with empty data.
	m_renderedSceneTextureBuffer.reset( new Texture() );
	glBindTexture( GL_TEXTURE_2D, m_renderedSceneTextureBuffer->GetTextureID() );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Engine::GetInstance().GetApplicationWindow().GetScreenWidth(),
		Engine::GetInstance().GetApplicationWindow().GetScreenHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	//Create the Depth Buffer for the render buffer.
	GLuint depthRenderBuffer;
	glGenRenderbuffers( 1, &depthRenderBuffer );
	glBindRenderbuffer( GL_RENDERBUFFER, depthRenderBuffer );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Engine::GetInstance().GetApplicationWindow().GetScreenWidth(), Engine::GetInstance().GetApplicationWindow().GetScreenHeight() );
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer );

	//Lastly, configure the frame buffer.
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderedSceneTextureBuffer->GetTextureID(), 0 );
	const GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers( 1, drawBuffers );

	glBindTexture( GL_TEXTURE_2D, NULL );
	glBindFramebuffer( GL_FRAMEBUFFER, NULL );

	//Create the frame buffer's mesh used to draw the final scene to the screen.
	std::vector< float > frameBufferVertexData = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		-1.0f, 1.0f,
		-1.0f, -1.0f
	};
	std::vector< float > frameBufferTextureCoordinates = {
		0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f
	};

	m_frameBufferMesh.reset( new Mesh() );
	m_frameBufferMesh->SetMaterial( std::shared_ptr< Material >( new Material( ResourceManager::GetInstance().GetShader( "ScreenFrameBufferShader" ) ) ) );
	m_frameBufferMesh->GetMaterial()->AddMaterialParameter( "activeTexture", std::shared_ptr< TextureParameter >( new TextureParameter( "activeTexture", m_renderedSceneTextureBuffer ) ) );
	m_frameBufferMesh->BindVertexAttribute( "vertexPosition", frameBufferVertexData, 2 );
	m_frameBufferMesh->BindVertexAttribute( "textureCoordinates", frameBufferTextureCoordinates, 2 );

	return true;
}




//Render the contents of the frame buffer to the screen to be displayed.
void Renderer::RenderFrameBufferToScreen()
{
	m_frameBufferMesh->GetMaterial()->BindInstanceParameters();
	glDrawArrays( GL_TRIANGLES, 0, 6 );
	glBindTexture( GL_TEXTURE_2D, NULL );
}




//Render a mesh to be displayed when the back buffer is flipped.
void Renderer::DrawMesh( std::shared_ptr< Mesh > meshData )
{
	glm::mat4 modelTransform = Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCamera().GetProjectionMatrix() * meshData->GetModelTransform();
	meshData->GetMaterial()->BindInstanceParameters();
	meshData->GetMaterial()->SetUniform( "transformationMatrix", modelTransform );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, meshData->GetIndexBufferObject() );
	glDrawElements( GL_TRIANGLES, meshData->GetNumVertices(), GL_UNSIGNED_INT, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );
}
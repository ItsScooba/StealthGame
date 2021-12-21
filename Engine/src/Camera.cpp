#include "Camera.h"

#include "Engine.h"

#include <glm\gtc\matrix_transform.hpp>

#include "Material.h"
#include "World.h"







Camera::Camera()
	: m_position( 0.0f, 0.0f, 0.0f ), m_viewMatrix( glm::mat4( 1.0f ) ), m_pitch( 0.0f ), m_yaw( 0.0f ),
	m_viewportWidth( ( float ) Engine::GetInstance().GetApplicationWindow().GetScreenWidth() ), 
	m_viewportHeight( ( float ) Engine::GetInstance().GetApplicationWindow().GetScreenHeight() )
{
	const float MIN_DEPTH = -512.0f, MAX_DEPTH = 512.0f;

	//Set the projection matrix.
	m_projectionMatrix =
		glm::ortho(
			0.0f, m_viewportWidth,
			0.0f, m_viewportHeight,
			MIN_DEPTH, MAX_DEPTH
			);

	BuildViewMatrix();

}




Camera::~Camera()
{

}




void Camera::AddPostProcessEffect( std::shared_ptr< Mesh > postProcessEffect )
{
	m_postProcessEffects.push_back( postProcessEffect );
}




//Update the camera's game logic.
void Camera::UpdateFogOfWar( World& gameWorld )
{
}




glm::vec3 Camera::Unproject( float screenX, float screenY )
{
	glm::vec3 unprojectedPoint( -1.0f, -1.0f, -1.0f );
	unprojectedPoint = glm::unProject( glm::vec3( screenX, screenY, 0.0f ), m_viewMatrix, m_projectionMatrix, glm::vec4( 0.0f, 0.0f, m_viewportWidth, m_viewportHeight ) );
	return unprojectedPoint;
}




void Camera::Translate( glm::vec3 translationVector )
{
	m_position += translationVector;
	BuildViewMatrix();
}




void Camera::SetPitchDegrees( float pitchInDegrees )
{
	m_pitch = pitchInDegrees;
	BuildViewMatrix();
}




void Camera::SetYawDegrees( float yawInDegrees )
{
	m_yaw = yawInDegrees;
	BuildViewMatrix();
}




void Camera::BuildViewMatrix()
{
	//Center the viewport before performing any transforms.
	glm::mat4 translationMatrix = glm::translate( glm::mat4( 1.0f ), 
		glm::vec3( ( Engine::GetInstance().GetApplicationWindow().GetScreenWidth() / 2.0f ), ( Engine::GetInstance().GetApplicationWindow().GetScreenHeight() / 2.0f ), 0.0f ) );
	translationMatrix = glm::translate( translationMatrix, -m_position );
	translationMatrix = glm::translate( translationMatrix,
		glm::vec3( -( Engine::GetInstance().GetApplicationWindow().GetScreenWidth() / 2.0f ), -( Engine::GetInstance().GetApplicationWindow().GetScreenHeight() / 2.0f ), 0.0f ) );

	glm::mat4 rotX = glm::rotate( glm::mat4( 1.0f ), -m_pitch, glm::vec3( 1.0f, 0.0f, 0.0f ) );
	glm::mat4 rotY = glm::rotate( glm::mat4( 1.0f ), -m_yaw, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	glm::mat4 rotationMatrix = rotY * rotX;

	glm::mat4 scaleMatrix = glm::scale( glm::mat4( 1.0f ), glm::vec3( 1.0f, 1.0f, -1.0f ) );

	m_viewMatrix =  translationMatrix * rotationMatrix * scaleMatrix;
}
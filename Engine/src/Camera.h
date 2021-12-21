#pragma once

#include <vector>
#include <memory>

#include <glm\glm.hpp>
#include <gl\glew.h>




//Forward Declares.
class World;
class Mesh;



class Camera
{
public:



	Camera();
	~Camera();

	void AddPostProcessEffect( std::shared_ptr< Mesh > postProcessEffectMesh );
	void UpdateFogOfWar( World& gameWorld );

	glm::vec3 Unproject( float screenX, float screenY );
	
	void Translate( glm::vec3 translationVector );
	void SetPitchDegrees( float pitchInDegrees );
	void SetYawDegrees( float yawInDegrees );
	



private:


	void BuildViewMatrix();


private:


	glm::mat4 m_viewMatrix, m_projectionMatrix;

	float m_viewportWidth, m_viewportHeight;
	glm::vec3 m_position;
	float m_pitch, m_yaw;

	std::vector< std::shared_ptr< Mesh > > m_postProcessEffects;


public:


	const glm::mat4& GetViewMatrix() { return m_viewMatrix; }
	const glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
	const glm::vec3& GetPosition() { return m_position; }
	const float& GetPitchDegrees() { return m_pitch; }
	const float& GetYawDegrees() { return m_yaw; }
	const std::vector< std::shared_ptr< Mesh > >& GetPostProcessEffects() { return m_postProcessEffects; }

};
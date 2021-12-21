#pragma once



#include <memory>
#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "AnimationPose.h"












struct Socket
{
	Socket( std::string socketName, glm::vec3 socketPosition = glm::vec3( 0.0f, 0.0f, 0.0f ) )
		: socket_name( socketName ), socket_position( socketPosition ), socket_rotation( 0.0f, 0.0f, 0.0f )
	{
	}



	const std::string socket_name;
	glm::vec3 socket_position;
	glm::vec3 socket_rotation;

};











//Skeleton with bones, joins, and sockets that is used for animation and attachment of child objects.
class SkeletalData
{
public:


	SkeletalData();
	~SkeletalData();

	void AddSocket( Socket* newSocket );

	void ApplyPose( std::shared_ptr< AnimationPose > pose );


private:


	std::vector< std::shared_ptr< Socket > > m_sockets;


public:


	const std::vector< std::shared_ptr< Socket > >& GetSockets() { return m_sockets; }

};
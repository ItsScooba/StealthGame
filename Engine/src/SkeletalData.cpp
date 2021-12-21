#include "SkeletalData.h"


















SkeletalData::SkeletalData()
{

}




SkeletalData::~SkeletalData()
{

}




void SkeletalData::AddSocket( Socket* newSocket )
{
	m_sockets.push_back( std::shared_ptr< Socket >( newSocket ) );
}




//Apply a pose compatible with this skeleton.
void SkeletalData::ApplyPose( std::shared_ptr< AnimationPose > pose )
{
	//Apply each sockets transform based on the current pose of the animation.
	std::map< std::string, socket_transform >::iterator socketTransformIter = pose->socket_transforms.begin();
	while ( socketTransformIter != pose->socket_transforms.end() ) {
		for ( std::shared_ptr< Socket > socket : m_sockets ) {
			if ( socketTransformIter->first == socket->socket_name ) {
				socket->socket_position = socketTransformIter->second.first;
				socket->socket_rotation = socketTransformIter->second.second;
				break;
			}
		}
		socketTransformIter++;
	}
}
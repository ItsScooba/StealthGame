#include "AnimationComponent.h"

#include "AnimationSystem.h"












AnimationComponent::AnimationComponent( std::shared_ptr< GameObject > parentGameObject, std::shared_ptr< AnimationPose > basePose )
	: Component( ComponentType::c_ANIMATION, parentGameObject ), m_basePose( basePose ), m_activeAnimation( nullptr )
{
}




AnimationComponent::~AnimationComponent()
{

}




//Add an animaiton that can be used by the parent entity.
void AnimationComponent::AddAnimation( std::string animationID, std::shared_ptr< Animation > animation )
{
	m_animations.emplace( animationID, animation );
}




//Try to start playing a requested animation.
bool AnimationComponent::PlayAnimation( std::string animationID )
{
	std::map< std::string, std::shared_ptr< Animation > >::iterator animationIter = m_animations.find( animationID );
	if ( animationIter == m_animations.end() ) 
		return false;
	
	m_activeAnimation = animationIter->second;
	m_activeAnimation->Start();

	return true;
}




//Stop playing any currently playing animation.
void AnimationComponent::StopPlayingAnimation()
{
	if( m_activeAnimation != NULL )
		m_activeAnimation->Stop();
	m_activeAnimation = NULL;
}
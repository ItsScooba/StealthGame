#pragma once



#include <memory>
#include <map>
#include <string>

#include "Component.h"

#include "Animation.h"



//Forward Declares.
class AnimationSystem;






//Component used to store and manage animations used by the entity it's attached to.
class AnimationComponent : public Component
{

	friend class AnimationSystem;

public:


	AnimationComponent( std::shared_ptr< GameObject > parentGameObject, std::shared_ptr< AnimationPose > basePose );
	~AnimationComponent();

	void AddAnimation( std::string animationID, std::shared_ptr< Animation > animation );
	bool PlayAnimation( std::string animationID );
	void StopPlayingAnimation();

	std::shared_ptr< Animation > GetActiveAnimation() { return m_activeAnimation; }


public:


	SkeletalData skeletal_data;


private:


	std::shared_ptr< AnimationPose > m_basePose;
	std::map< std::string, std::shared_ptr< Animation > > m_animations;
	std::shared_ptr< Animation > m_activeAnimation;


public:


	std::shared_ptr< AnimationPose > GetBasePose() { return m_basePose; }

};
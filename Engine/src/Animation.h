#pragma once


#include <memory>
#include <vector>
#include <map>
#include <string>

#include "SkeletalData.h"
#include "Timer.h"
#include "AnimationPose.h"















//Class used to store information about the animation at a given point in time.
struct KeyFrame
{
	KeyFrame( float duration, std::shared_ptr< AnimationPose > keyframePose )
		: frame_duration( duration ), keyframe_pose( keyframePose )
	{}

	const float frame_duration;											//How long to stay on this key frame before moving onto the next one.
	std::shared_ptr< AnimationPose > keyframe_pose;							//The way the animation should look when this is the active keyframe.


};














class Animation
{
public:


	Animation();
	~Animation();
	
	void AddKeyFrame( std::shared_ptr< KeyFrame > keyFrame );

	void Start();
	void Stop();
	void Tick();

	float GetAnimationLength();
	std::shared_ptr< AnimationPose > GetCurrentPose();


protected:


	std::vector< std::shared_ptr< KeyFrame > > m_keyFrames;						//List of frames' data that make up the animation as a whole.
	std::shared_ptr< KeyFrame > m_currentKeyframe;								//The frame being used to draw the animation right now.
	int m_currentKeyframeIndex;
	
	bool m_isPlaying;															//Whether or not the animation is currently playing.
	bool m_loopAnimation;														//Whether or not to loop this animation and repeat after reaching the end.
	Timer m_animationTimer;	

	bool m_isPoseDirty;															//Whether or not the current pose in the animation needs to be applied to the skeleton.


public:


	const bool& IsPoseDirty() { return m_isPoseDirty; }
	void SetPoseDirtyFalse() { m_isPoseDirty = false; }

};
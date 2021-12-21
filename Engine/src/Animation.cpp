#include "Animation.h"










Animation::Animation()
	: m_isPlaying( false ), m_loopAnimation( false ),
	m_currentKeyframeIndex( -1 ), m_currentKeyframe( NULL ), m_isPoseDirty( false )
{

}




Animation::~Animation()
{

}




//Add a keyframe to the animation. ( a point at which the animation changes )
void Animation::AddKeyFrame( std::shared_ptr< KeyFrame > keyFrame )
{
	m_keyFrames.push_back( keyFrame );
}




//Start playing the animation from the beginning.
void Animation::Start()
{
	if ( m_keyFrames.empty() ) return;

	m_currentKeyframe = m_keyFrames.front();
	m_currentKeyframeIndex = 0;
	m_isPlaying = true;
	m_animationTimer.RestartTimer();

	m_isPoseDirty = true;
}




//Stop playing the animation.
void Animation::Stop()
{
	m_isPlaying = false;
	m_currentKeyframe = NULL;
	m_animationTimer.StopTimer();
}




//Update the animation.
void Animation::Tick()
{
	//Check to see if it's time to advance the animation.
	if ( m_animationTimer.GetElapsedTimeInSeconds() >= m_currentKeyframe->frame_duration ) {
		m_currentKeyframeIndex++;

		//Make sure the animation isn't at the end. If so, check for repeat.
		if ( m_currentKeyframeIndex >= m_keyFrames.size() ) {
			if ( m_loopAnimation )
				m_currentKeyframeIndex = 0;
			else {
				Stop();
				return;
			}
		}

		//Otherwise, simply advance to the next frame and restart the timer.
		m_currentKeyframe = m_keyFrames.at( m_currentKeyframeIndex );
		m_animationTimer.RestartTimer();

		m_isPoseDirty = true;
	}
}




std::shared_ptr< AnimationPose > Animation::GetCurrentPose()
{
	if ( m_currentKeyframe == nullptr )
		return NULL;
	else
		return m_currentKeyframe->keyframe_pose;
}




//Get the total length in seconds of the animation if played at normal speed.
float Animation::GetAnimationLength()
{
	float totalLength = 0.0f;
	for( std::shared_ptr< KeyFrame > keyFrame : m_keyFrames ) {
		totalLength += keyFrame->frame_duration;
	}

	return totalLength;
}
#include "Timer.h"



#include "SDL2\SDL.h"









Timer::Timer() : m_timerStartTime( -1.0f )
{
	
}




Timer::~Timer()
{
	
}




//Start the timer, with elapsed time set to 0.
void Timer::StartTimer()
{
	m_timerStartTime = SDL_GetTicks();
}




//Stop this timer from running.
void Timer::StopTimer()
{

}




//Restart the timer to 0 seconds elapsed and start it.
void Timer::RestartTimer()
{
	m_timerStartTime = SDL_GetTicks();
}




//Get the total elapsed time that this timer has been running for.
float Timer::GetElapsedTimeInSeconds()
{
	return ( SDL_GetTicks() - m_timerStartTime ) / 1000.0f;
}
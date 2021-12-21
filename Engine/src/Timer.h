#pragma once













//Class used to help keep time
class Timer
{
public:


	Timer();
	~Timer();

	void StartTimer();
	void StopTimer();
	void RestartTimer();

	float GetElapsedTimeInSeconds();


private:


	float m_timerStartTime;												//Time returned from SDL when this timer was started.



};

#ifndef MISCELLANEOUS_TIMER_H_
#define MISCELLANEOUS_TIMER_H_

#include <SDL2/SDL.h>

class Timer
{
public:
	//Initializes variables
	Timer();

	//The various clock actions
	void Start();
	void Stop();
	void Pause();
	void Unpause();

	//Gets the timer's time
	uint32_t GetTicks();

	//Checks the status of the timer
	bool IsStarted();
	bool IsPaused();
private:
	//The clock time when the timer started
	uint32_t StartTicks;

	//The ticks stored when the timer was paused
	uint32_t PausedTicks;

	//The timer status
	bool Paused;
	bool Started;
};

#endif /* MISCELLANEOUS_TIMER_H_ */

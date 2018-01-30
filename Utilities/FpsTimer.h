
#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include "SDL2/SDL.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class FpsTimer
{
public:
	//Initializes variables
	FpsTimer();

	//The various clock actions
	void Start();
	void Stop();
	void Pause();
	void Unpause();

	//Gets the timer's time
	uint32_t GetTicks();
	uint32_t GetFrames();

	//Checks the status of the timer
	bool IsStarted();
	bool IsPaused();

	void IncrementFrameCount();
	void CalcFrames();
	void DelayFrames();
private:
	//The clock time when the timer started
	uint32_t StartTicks;

	//The ticks stored when the timer was paused
	uint32_t PausedTicks;

	//The timer status
	bool Paused;
	bool Started;

	float avgFps;
	uint32_t countedFrames;
	uint32_t frameTicks;
};

#endif /* TIMER_H_ */

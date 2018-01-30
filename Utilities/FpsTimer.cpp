
#include "FpsTimer.h"

FpsTimer::FpsTimer()
{
    //Initialize the variables
    StartTicks = 0;
    PausedTicks = 0;

    Paused = false;
    Started = false;

    avgFps = 0;

    countedFrames = 0;
    frameTicks = 0;
}

void FpsTimer::Start()
{
    //Start the timer
    Started = true;

    //Unpause the timer
    Paused = false;

    //Get the current clock time
    StartTicks = SDL_GetTicks();
    PausedTicks = 0;
}

void FpsTimer::Stop()
{
    //Stop the timer
    Started = false;

    //Unpause the timer
    Paused = false;

    //Clear tick variables
    StartTicks = 0;
    PausedTicks = 0;
}

void FpsTimer::Pause()
{
    //If the timer is running and isn't already paused
    if( Started && !Paused )
    {
        //Pause the timer
        Paused = true;

        //Calculate the paused ticks
        PausedTicks = SDL_GetTicks() - StartTicks;
        StartTicks = 0;
    }
}

void FpsTimer::Unpause()
{
    //If the timer is running and paused
    if( Started && Paused )
    {
        //Unpause the timer
        Paused = false;

        //Reset the starting ticks
        StartTicks = SDL_GetTicks() - PausedTicks;

        //Reset the paused ticks
        PausedTicks = 0;
    }
}

uint32_t FpsTimer::GetTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if( Started )
    {
        //If the timer is paused
        if( Paused )
        {
            //Return the number of ticks when the timer was paused
            time = PausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - StartTicks;
        }
    }

    return time;
}

uint32_t FpsTimer::GetFrames()
{
	return countedFrames;
}

void FpsTimer::IncrementFrameCount()
{
	countedFrames++;
}

void FpsTimer::CalcFrames()
{
	 //Calculate and correct fps
	avgFps = countedFrames / ( GetTicks() / 1000.f );
	if( avgFps > 2000000 )
	{
		avgFps = 0;
	}
	std::cout << avgFps << std::endl;
}

void FpsTimer::DelayFrames()
{
	//If frame finished early
	frameTicks = GetTicks();
	if( frameTicks < SCREEN_TICKS_PER_FRAME )
	{
		//Wait remaining time
		SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
	}
}

bool FpsTimer::IsStarted()
{
    //FpsTimer is running and paused or unpaused
    return Started;
}

bool FpsTimer::IsPaused()
{
    //FpsTimer is running and paused
    return Paused && Started;
}

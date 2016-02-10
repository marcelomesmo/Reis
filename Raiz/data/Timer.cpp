#include "Timer.h"

Timer::Timer()
{
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	running = false;
}

void Timer::start()
{
	//Start the timer
	running = true;

	//Unpause the timer
	paused = false;

	//Get the current clock time
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

// The stop function basically reinitialize all the variables.
void Timer::stop()
{
	//Stop the timer
	running = false;

	//Unpause the timer
	paused = false;

	//Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if (running && !paused)
	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused
	if (running && paused)
	{
		//Unpause the timer
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (running)
	{
		//If the timer is paused
		if (paused)
		{
			//Return the number of ticks when the timer was paused
			time = pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool Timer::isRunning()
{
	//Timer is running and paused or unpaused
	return running;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return paused && running;
}

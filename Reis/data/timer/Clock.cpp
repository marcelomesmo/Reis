#include "Clock.h"

Clock::Clock()
{
	//Init variables
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	running = false;
}

void Clock::start()
{
	//Start the clock
	running = true;

	//Unpause the clock
	paused = false;

	//Get the current clock time
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

// The stop function basically reinitialize all the variables.
void Clock::stop()
{
	//Stop the clock
	running = false;

	//Unpause the clock
	paused = false;

	//Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

void Clock::pause()
{
	//If the clock is running and isn't already paused
	if (running && !paused)
	{
		//Pause the clock
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Clock::unpause()
{
	//If the clock is running and paused
	if (running && paused)
	{
		//Unpause the clock
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

Uint32 Clock::getTicks()
{
	//The actual clock time
	Uint32 time = 0;

	//If the clock is running
	if (running)
	{
		//If the clock is paused
		if (paused)
		{
			//Return the number of ticks when the clock was paused
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

float Clock::getTime()
{
	float timeSeconds = (this->getTicks() / 1000.f);

	std::cout << std::fixed << std::setprecision(3) << timeSeconds << " s" << std::endl;

	return timeSeconds;
}

bool Clock::isRunning()
{
	//Clock is running and paused or unpaused
	return running;
}

bool Clock::isPaused()
{
	//Clock is running and paused
	return paused && running;
}

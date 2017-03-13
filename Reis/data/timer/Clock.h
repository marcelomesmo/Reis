#ifndef CLOCK_H
#define CLOCK_H

#include <SDL.h>
#include <iomanip>
#include <iostream>

/**
 * @brief      The application time based clock.
 * 
 * @author     marcelomesmo
 */
class Clock
{
public:
	/**
	 * @brief      Init clock.
	 */
	Clock();

	/**
	 * @brief      Start the clock timer.
	 */
	void start();
	/**
	 * @brief      Stop the clock timer.
	 */
	void stop();
	/**
	 * @brief      Pause the clock timer.
	 */
	void pause();
	/**
	 * @brief      Unpause the clock timer.
	 */
	void unpause();

	/**
	 * @brief      Gets the clock current time.
	 *
	 * @return     Current time in ticks (milliseconds).
	 */
	Uint32 getTicks();

	/**
	 * @brief      Gets the clock current time in seconds.
	 *
	 * @return     Current time in seconds.
	 */
	float getTime();

	/**
	 * @brief      Check status of the clock.
	 *
	 * @return     True if clock has started and is running.
	 */
	bool isRunning();
	/**
	 * @brief      Checks the status of the timer.
	 *
	 * @return     True if clock is paused.
	 */
	bool isPaused();

private:
	/**
	 * The time (in ticks) when the clock started.
	 */
	Uint32 startTicks;

	/**
	 * The time (in ticks) stored when the clock was paused.
	 */
	Uint32 pausedTicks;

	/**
	 * True if the clock is paused.
	 */
	bool paused;
	/**
	 * True if the clock has started and is running.
	 */
	bool running;
};

#endif
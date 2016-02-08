#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

/**
 * @brief      The application time based clock.
 * 
 * @author     marcelomesmo
 */
class Timer
{
public:
	/**
	 * @brief      Initializes timer.
	 */
	Timer();

	/**
	 * @brief      Start the timer's clock.
	 */
	void start();
	/**
	 * @brief      Stop the timer's clock.
	 */
	void stop();
	/**
	 * @brief      Pause the timer's clock.
	 */
	void pause();
	/**
	 * @brief      Unpause the timer's clock.
	 */
	void unpause();

	/**
	 * @brief      Gets the timer's current time.
	 *
	 * @return     Current time in ticks.
	 */
	Uint32 getTicks();

	/**
	 * @brief      Checks the status of the timer.
	 *
	 * @return     true if timer has started and is running.
	 */
	bool isRunning();
	/**
	 * @brief      Checks the status of the timer.
	 *
	 * @return     true if timer is paused.
	 */
	bool isPaused();

private:
	/**
	 * The clock time when the timer started.
	 */
	Uint32 startTicks;

	/**
	 * The ticks stored when the timer was paused.
	 */
	Uint32 pausedTicks;

	/**
	 * True if the timer is paused.
	 */
	bool paused;
	/**
	 * True if the timer has started and is running.
	 */
	bool running;
};

#endif
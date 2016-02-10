#ifndef TRANSITION_H
#define TRANSITION_H

#include "../Game.h"

/**
 * @brief      A simple interface for the Transition between two GameStates.
 * 
 * @author     marcelomesmo
 */
class Transition
{
public:
	virtual ~Transition() { }

	/**
	 * @brief      Updates the transition effects.
	 *
	 * @param      game   The running Game object.
	 * @param[in]  delta  The amount of time in miliseconds since last update.
	 */
	virtual void update(Game* game, float delta) = 0;
	/**
	 * @brief      Render the Transition before the current GameState rendering.
	 *
	 * @param      g     The Graphics context to use for rendering.
	 */
	virtual void preRender(Graphics& g) = 0;
	/**
	 * @brief      Render the Transition after the current GameState rendering.
	 *
	 * @param      g     The Graphics context to use for rendering.
	 */
	virtual void postRender(Graphics& g) = 0;

	/**
	 * @brief      Check if the Transition has finished.
	 *
	 * @return     True if the Transition is complete.
	 */
	virtual bool isFinished() = 0;
};

#endif
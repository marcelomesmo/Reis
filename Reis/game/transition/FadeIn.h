#ifndef FADEIN_H
#define FADEIN_H

#include "Transition.h"

/**
 * @brief      A Transition to Fade In from a given Color.
 *
 * @author     marcelomesmo
 */
class FadeIn : public Transition
{
public:
	/**
	 * @brief      Create a new Fade In transition.
	 *
	 * @param[in]  c     The Color we are going to Fade In from.
	 */
	FadeIn(Color c = Color::BLACK);
	/**
	 * @brief      Create a new Fade In Transition.
	 *
	 * @param[in]  c     The Color we are going to Fade In from.
	 * @param[in]  time  The time it takes for the transition to finish.
	 */
	FadeIn(Color c, Uint32 time = 500);
	/**
	 * @brief      Updates the transition effects.
	 *
	 * @param      game   The running Game object.
	 * @param[in]  delta  The amount of time in miliseconds since last update.
	 */
	void update(Game* game, float delta);
	/**
	 * @brief      Render the Transition before the current Scene rendering.
	 *
	 * @param      g     The Graphics context to use for rendering.
	 */
	void preRender(Graphics& g);
	/**
	 * @brief      Render the Transition after the current Scene rendering.
	 *
	 * @param      g     The Graphics context to use for rendering.
	 */
	void postRender(Graphics& g);
	
	/**
	 * @brief      Check if the Transition has finished.
	 *
	 * @return     True if the Transition is complete.
	 */
	bool isFinished();

	/**
	* @brief      Set Transition color.
	*
	* @param[in]  c      A enum Color parameter.
	* @param[in]  alpha  The initial alpha value for the Color.
	*/
	void setColor(Color c, Uint8 alpha = 255);

private:
	/**
	 * The Color to Fade In from.
	 */
	SDL_Color cor;
	/**
	 * Current Color alpha value.
	 */
	float alpha;
	/**
	 * The time it takes for the transition to finish.
	 */
	Uint32 fadeTime;
};

#endif

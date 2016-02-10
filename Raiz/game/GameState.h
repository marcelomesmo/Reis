#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"

/**
 * @brief      Interface for the different stages of the game (menu, loading screen, ingame, credits etc).
 * 
 * @author     marcelomesmo
 */
class GameState
{

public:
	/**
	 * @brief      Inits the GameState. Should include objects and variables initialization. It's called before the game loop starts.
	 *
	 * @param      game  The Game object application in which the GameState is hosted.
	 */
	virtual void init(Game* game) = 0;
	/**
	 * @brief      Clear the GameState.
	 */
	virtual void free() = 0;

	/**
	 * @brief      Pause the GameState.
	 */
	virtual void pause() = 0;
	/**
	 * @brief      Unpause the GameState.
	 */
	virtual void resume() = 0;

	/**
	 * @brief      Updates the GameState. Should include input handling, IA logic and physics.
	 *
	 * @param      game   The Game object application in which the GameState is hosted.
	 * @param[in]  delta  The amount of time in milliseconds since last update.
	 */
	virtual void update(Game* game, Input& input, float delta) = 0;
	/**
	 * @brief      Render the GameState. Render the game's screen here.
	 *
	 * @param      game  The Game object application in which the GameState is
	 *                   hosted.
	 * @param      g     The Graphics context to use for rendering.
	 */
	virtual void render(Game* game, Graphics& g) = 0;

	/**
	 * @brief      Get the ID of this state.
	 *
	 * @return     The game unique ID of this state.
	 */
	virtual int getID() = 0;

};

#endif
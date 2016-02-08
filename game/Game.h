#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
using namespace std;

#include "../graphics/Graphics.h"
//#include "../input/Input.h"
#include "../data/Timer.h"

/// GameState foward declaration to resolve circular depedency.
class GameState;
/// Fade foward declaration to resolve circular dependency.
class Transition;

/**
 * @brief      The main game class that implements GameStates stack, Graphics rendering and Input management. Must exist in any game being developed. 
 * 
 * @author     marcelomesmo
 */
class Game
{

public:

	/**
	 * @brief      Init Game window and Graphics.
	 *
	 * @param[in]  title       Game window's title.
	 * @param[in]  width       Screen width.
	 * @param[in]  height      Screen height.
	 * @param[in]  fullscreen  Set fullscreen mode.
	 */
	void init(const char* title, int width = 640, int height = 480, 
		bool fullscreen = false, bool capFrame = true);
	/**
	 * @brief      Clear the Game.
	 */
	void free();

	/**
	 * @brief      Init the list of GameStates.
	 *
	 * @param[in]  allStatesHere  A std::vector of GameStates.
	 */
	void initStateList(vector<GameState*> allStatesHere);
	/**
	 * @brief      Enter a specified GameState.
	 *
	 * @param[in]  id     The ID of the GameState to enter.
	 * @param      leave  The transition used when leaving the current state.
	 * @param      enter  The transition used when entering the new game state.
	 */
	void enterState(int id, Transition* leave = NULL, Transition* enter = NULL);

	/**
	 * @brief      Start running the Game.
	 */
	void start();
	/**
	 * @brief      Exits the Game main loop.
	 */
	void quit();

	/**
	 * @brief      Set window target FramesPerSecond (60fps default).
	 *
	 * @param[in]  targetFrameRate  An integer for target FramesPerSecond.
	 */
	void setTargetFrameRate(int targetFrameRate);
	/**
	 * @brief      Switch window fullscreen.
	 *
	 * @param[in]  set_fullscreen  True in case fullscreen.
	 */
	void setFullScreen(bool set_fullscreen);

private:
	/**
	 * The Graphics component. Used to render stuff on screen.
	 */
	Graphics g;

	/**
	 * @brief      Adds a delay to the Game window based on target FPS.
	 */
	void capFrameRate();

	/**
	 * @brief      Changes the GameState in the stack.
	 *
	 * @param      state  Target GameState.
	 */
	void changeState(GameState* state);
	/**
	 * @brief      Push GameState in the stack.
	 *
	 * @param      state  New GameState.
	 */
	void pushState(GameState* state);
	/**
	 * @brief      Pops GameState from the stack.
	 */
	void popState();

	/**
	 * @brief      Check if Game is running to continue the game loop.
	 *
	 * @return     True if Game is running.
	 */
	bool isRunning();

	/**
	 * @brief      Update current GameState.
	 */
	void update();
	/**
	 * @brief      Render current GameState.
	 */
	void render();

	/**
	 * List of GameStates.
	 */
	vector<GameState*> statesList;

	/**
	 * List of current GameStates in the stack.
	 */
	vector<GameState*> states;

	/** The transition being used to enter the state */
	Transition* enterTransition;
	/** The transition being used to leave the state */
	Transition* leaveTransition;
	int nextState;

	// Check if Game is running and operative. :)
	bool running;

	// Check if Game is in fullscreen.
	bool fullscreen;
	
	/**
	 * Variables for update's timer.
	 */
	float delta;
	int thisTime;
	int lastTime;

	/**
	 * Variables to cap frame rate.
	 */
	Timer capTimer;
	int frameTicks;				// ticks since last frame
	bool doCapFrame;			// true in case we want to Cap Frame Rate
	int screenTargetFPS;		// target FPS
	int screenTicksPerFrame;	// how many ticks we want to wait (skip) until next frame update (1000 / target FPS)
};

#endif
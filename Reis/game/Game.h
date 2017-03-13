#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
using namespace std;

#include "../graphics/Graphics.h"
#include "../input/Input.h"
#include "../data/timer/Clock.h"

/// Scene foward declaration to resolve circular depedency.
class Scene;
/// Fade foward declaration to resolve circular dependency.
class Transition;

/**
 * @brief      The main game class that implements stage scene/game state stacks, Graphics rendering and Input management. Must exist in any game being developed. 
 * 
 * @author     marcelomesmo
 */
class Game
{

public:

	/**
	 * @brief      Create a new Game.
	 *
	 * @param[in]  title       Game window's title.
	 * @param[in]  width       Screen width.
	 * @param[in]  height      Screen height.
	 * @param[in]  fullscreen  Set fullscreen mode.
	 */
	void create(const char* title, int width = 640, int height = 480, 
		bool fullscreen = false, bool capFrame = true);
	/**
	 * @brief      Clear the Game and finish.
	 */
	void end();

	/**
	 * @brief      Init the list of Scenes.
	 *
	 * @param[in]  allScenesHere  A std::vector of Scenes.
	 */
	void prepareScenes(vector<Scene*> allScenesHere);
	/**
	 * @brief      Enter a specified Scene.
	 *
	 * @param[in]  id     The ID of the Scene to enter.
	 * @param      leave  The transition used when leaving the current scene.
	 * @param      enter  The transition used when entering the new game scene.
	 */
	void enterScene(int id, Transition* leave = NULL, Transition* enter = NULL);

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
	* The Input manager. Used to handle keyboard, mouse and controller input.
	*/
	Input input;

	/**
	 * @brief      Adds a delay to the Game window based on target FPS.
	 */
	void capFrameRate();

	/**
	 * @brief      Changes the Scene in the stack.
	 *
	 * @param      scene  Target Scene.
	 */
	void changeScene(Scene* scene);
	/**
	 * @brief      Push Scene in the stack.
	 *
	 * @param      scene  New Scene.
	 */
	void pushScene(Scene* scene);
	/**
	 * @brief      Pops Scene from the stack.
	 */
	void popScene();

	/**
	 * @brief      Check if Game is running to continue the game loop.
	 *
	 * @return     True if Game is running.
	 */
	bool isRunning();

	/**
	 * @brief      Update current Scene.
	 */
	void update();
	/**
	 * @brief      Render current Scene.
	 */
	void render();

	/**
	 * List of Scenes.
	 */
	vector<Scene*> scenesList;

	/**
	 * List of current Scenes in the stack.
	 */
	vector<Scene*> scenes;

	/** The transition being used to enter the scene */
	Transition* enterTransition;
	/** The transition being used to leave the scene */
	Transition* leaveTransition;
	int nextScene;

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
	Clock capTimer;
	int frameTicks;				// ticks since last frame
	bool doCapFrame;			// true in case we want to Cap Frame Rate
	int screenTargetFPS;		// target FPS
	int screenTicksPerFrame;	// how many ticks we want to wait (skip) until next frame update (1000 / target FPS)
};

#endif
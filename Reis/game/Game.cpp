#include "Game.h"
#include "Scene.h"
#include "transition/Transition.h"

void Game::create(const char* title, int width, int height, bool set_fullscreen, bool capFrame)
{
	g.init(title, width, height, set_fullscreen);
	fullscreen = set_fullscreen;

	input.init();

	// leaveTRansition
	leaveTransition = NULL;
	enterTransition = NULL;
	nextScene = 0;

	doCapFrame = capFrame;
	screenTargetFPS = 60;
	screenTicksPerFrame = 1000 / screenTargetFPS;

	running = true;

	delta = 0;
	thisTime = 0;
	lastTime = 0;

	frameTicks = 0;

	//printf("DEBUG: Game Init\n");
}

void Game::end()
{
	// Clean up all Scenes.
	while (!scenes.empty()) {
		scenes.back()->end();
		scenes.pop_back();
	}

	// Clean up Input
	input.free();
	// Clean first so Subsystem is cleared before SDL_Quit (in Graphics)

	// Clean up Graphics
	g.free();

	//printf("DEBUG: Game Cleanup\n");
}

// Init a list of all scenes with ID from 0 to allScenesHere.size-1
void Game::prepareScenes(vector<Scene*> allScenesHere)
{
	scenesList = allScenesHere;
	//cout << "Number of scenes: " << scenesList.size() << " \n";
}
// Push the scene by ID
void Game::enterScene(int id, Transition* leave, Transition* enter)
{
	// Se o ID for incorreto nao muda
	if ((unsigned)id >= this->scenesList.size()) cout << "ERROR: Invalid scene ID " << id << ".\n";
	// Se o ID for correto muda de estado
	else
	{
		// Pega o ID do proximo scene
		nextScene = id;

		// Se tiver FadeIn e ja nao estiver em transicao
		if (enter != NULL)
		{
			enterTransition = enter;
		}

		// Se tiver um FadeOut e ja nao estiver em transicao
		if (leave != NULL)
		{
			// Ativa o FadeOut
			leaveTransition = leave;
		}
		// Se nao, muda automaticamente
		else changeScene(scenesList[id]);
	}
}

void Game::changeScene(Scene* scene)
{
	// Clean up the current Scene.
	if (!scenes.empty()) {
		scenes.back()->end();
		scenes.pop_back();
	}

	// Reset Graphics to original Font and Color config
	g.reset();
	// This is intended to avoid Font and Color/BgColor changes persistence between Scenes
	// Reset Input to original scene (empty)
	input.clear();
	// This is intended to avoid key presses persistence between Scenes

	// store and init the new scene
	scenes.push_back(scene);
	scenes.back()->init(this);
}

void Game::pushScene(Scene* scene)
{
	// pause current scene
	if (!scenes.empty()) {
		scenes.back()->pause();
	}

	// store and init the new scene
	scenes.push_back(scene);
	scenes.back()->init(this);
}

void Game::popScene()
{
	// cleanup the current scene
	if (!scenes.empty()) {
		scenes.back()->end();
		scenes.pop_back();
	}

	// resume previous scene
	if (!scenes.empty()) {
		scenes.back()->resume();
	}
}

void Game::start()
{
	// Start first Scene
	if (scenesList.size() != 0)
	{
		changeScene(scenesList[0]);
		//printf("Early game, loading first scene\n");
	}
	else {
		printf("ERROR: We don't have first Scene initialization.\n"); 
		quit();
	}

	// Game main loop.
	while (isRunning())
	{
		update();
		render();

		capFrameRate();
	}
}

void Game::update()
{
	// Handle input events
	input.clear();
	input.update();

	// Calculate delta
	thisTime = SDL_GetTicks();
	delta = (float)(thisTime - lastTime) /1000;
	lastTime = thisTime;

	// Calculate delay based on TARGET FRAME RATE (60 fps)
	capTimer.start(); // restart timer

	if (leaveTransition != NULL)
	{
		leaveTransition->update(this, delta);
		if (leaveTransition->isFinished())
		{
			//printf("DEBUG: Finished LEAVE transition, loading Scene.\n");
			changeScene(scenesList[nextScene]);
			delete leaveTransition;
			leaveTransition = NULL;
		}
		else
			return;
		// Only goes pass this point when leaveTransition has finished (stop going on above 'return')
	}
	
	if (enterTransition != NULL)
	{
		enterTransition->update(this, delta);
		if (enterTransition->isFinished())
		{
			//printf("DEBUG: Finished ENTER transition, Scene fully loaded.\n");
			delete enterTransition;
			enterTransition = NULL;
		}
		else
			return;
		// Only updates scene if enterTransition has finished (stop going on above 'return')
	}

	// Let the current Scene update the game.
	scenes.back()->update(this, input, delta);
}

void Game::render()
{
	// Open Batch
	g.begin();

	// Pre-render transition here
	if (leaveTransition != NULL) leaveTransition->preRender(g);
	else if (enterTransition != NULL) enterTransition->preRender(g);

	// Let the current scene draw the screen
	scenes.back()->render(this, g);

	// Operate transitions (Post Render)
	if (leaveTransition != NULL) leaveTransition->postRender(g);
	else if (enterTransition != NULL) enterTransition->postRender(g);	// so vai renderizar qnd o leave terminar (leave = NULL)

	// Close Graphics Batch
	g.end();
}

void Game::capFrameRate()
{
	// give PC a break (opt)
	if (doCapFrame)
	{
		frameTicks = capTimer.getTicks();		// gets how long did it take to update() Scenes
		if (frameTicks < screenTicksPerFrame)
		{
			//Wait remaining time
			SDL_Delay(screenTicksPerFrame - frameTicks);
		}
	}
	else {
		// adicionar um delay a uma thread nao eh uma boa pratica
		SDL_Delay(1);
	}
}

void Game::setTargetFrameRate(int targetFrameRate)
{
	doCapFrame = true;
	screenTargetFPS = targetFrameRate;
	screenTicksPerFrame = 1000 / screenTargetFPS;
}

void Game::setFullScreen(bool set_fullscreen)
{
	fullscreen = set_fullscreen;
}

bool Game::isRunning()
{
	return running;
}

void Game::quit() 
{ 
	running = false;
}
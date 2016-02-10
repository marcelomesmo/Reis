#include "Game.h"
#include "GameState.h"
#include "transition/Transition.h"

void Game::init(const char* title, int width, int height, bool set_fullscreen, bool capFrame)
{
	g.init(title, width, height, set_fullscreen);
	fullscreen = set_fullscreen;

	input.init();

	// leaveTRansition
	leaveTransition = NULL;
	enterTransition = NULL;
	nextState = 0;

	doCapFrame = capFrame;
	screenTargetFPS = 60;
	screenTicksPerFrame = 1000 / screenTargetFPS;

	running = true;

	delta = 0;
	thisTime = 0;
	lastTime = 0;

	frameTicks = 0;

	printf("Game Init\n");

}

void Game::free()
{
	// Clean up all States.
	while (!states.empty()) {
		states.back()->free();
		states.pop_back();
	}

	// Clean up Graphics
	g.free();

	// Clean up Input
	input.free();

	printf("Game Cleanup\n");
}

// Init a list of all states with ID from 0 to allStatesHere.size-1
void Game::initStateList(vector<GameState*> allStatesHere)
{
	statesList = allStatesHere;
	cout << "Number of states: " << statesList.size() << " \n";
}
// Push the state by ID
void Game::enterState(int id, Transition* leave, Transition* enter)
{
	// Se o ID for incorreto nao muda
	if ((unsigned)id >= this->statesList.size()) cout << "Invalid state ID\n";
	// Se o ID for correto muda de estado
	else
	{
		// Pega o ID do proximo state
		nextState = id;

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
		else changeState(statesList[id]);
	}
}

void Game::changeState(GameState* state)
{
	// Clean up the current State.
	if (!states.empty()) {
		states.back()->free();
		states.pop_back();
	}

	// Reset Graphics to original Font and Color config
	g.reset();
	// This is intended to avoid Font and Color/BgColor changes persistence between GameStates
	// Reset Input to original state (empty)
	input.clear();
	// This is intended to avoid key presses persistence between GameStates

	// store and init the new state
	states.push_back(state);
	states.back()->init(this);
}

void Game::pushState(GameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->init(this);
}

void Game::popState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->free();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->resume();
	}
}

void Game::start()
{
	// Start first State
	if (statesList.size() != 0)
	{
		changeState(statesList[0]);
		//printf("Early game, loading first state\n");
	}
	else {
		printf("Error ocurred in initialization while loading first GameState."); 
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
			//printf("finished LEAVE transition, loading state\n");
			changeState(statesList[nextState]);
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
			//printf("finished ENTER transition, state fully loaded\n");
			delete enterTransition;
			enterTransition = NULL;
		}
		else
			return;
		// Only updates state if enterTransition has finished (stop going on above 'return')
	}

	// Let the current State update the game.
	states.back()->update(this, input, delta);
}

void Game::render()
{
	// Open Batch
	g.begin();

	// Pre-render transition here
	if (leaveTransition != NULL) leaveTransition->preRender(g);
	else if (enterTransition != NULL) enterTransition->preRender(g);

	// Let the current state draw the screen
	states.back()->render(this, g);

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
		frameTicks = capTimer.getTicks();		// gets how long did it take to update() gamestates
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
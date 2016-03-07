#include "Input.h"

void Input::init()
{
	// Inits lock/unlock
	this->isKeyboardLocked = false; 
	this->isMouseLocked = false; 
	for (int i = 0; i < MAX_CONTROLLERS; ++i) { this->isControllerLocked[i] = false; }

	// Inits mouse pos
	this->mouseX = 0;
	this->mouseY = 0;
	this->mouseDirX = 0;
	this->mouseDirY = 0;

	// Inits controller subsystem
	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) printf("Failed init Controller!\n");
	else printf("Success init Controller\n");

	numControllers = 0;
	lockInput(InputType::CONTROLLER);	// Init all controllers locked
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		// Init alreadly connected controllers and unlock them
		openController(i);
	}
	this->sensibility = 0.25;	// starts dead zone at 8000

	// Inits input
	this->do_quit = false;

	printf("Success init Input\n");
}

void Input::free()
{
	keyPressed.clear();
	keyReleased.clear();
	keyDown.clear();

	mousePressed.clear();
	mouseReleased.clear();
	mouseDown.clear();

	// Close all Controllers
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		joyPressed[i].button.clear();
		joyReleased[i].button.clear();
		joyDown[i].button.clear();

		axisPressed[i].button.clear();
		axisReleased[i].button.clear();
		axisDown[i].button.clear();

		closeController(i);
	}

	//joyPressed[currController].button.clear();
	//joyReleased[currController].button.clear();
	//joyDown[currController].button.clear();

	//axisPressed.clear();
	//axisReleased.clear();
	//axisDown.clear();

	// Close Controller subsystem
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	printf("Success close input\n");
}

// Clear the state of the keys
void Input::clear()
{
	// Clean keyPresses and keyReleases
	keyPressed.clear();
	keyReleased.clear();
	// keyDown isn't supossed to be clear because we need to store that until the key is released.

	// Clean mousePresses and mouseReleases
	mousePressed.clear();
	mouseReleased.clear();
	// Cleans mouse directions (to check if mouse has stopped moving)
	mouseDirX = 0;
	mouseDirY = 0;
	// mouseDown isn't supossed to be clear because we need to store that until the mouse button is released.
	
	// Clean controllerPresses and controllerReleases, including buttons (joy) and axis (axis)
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		joyPressed[i].button.clear();
		joyReleased[i].button.clear();

		axisPressed[i].button.clear();
		axisReleased[i].button.clear();

		// Cleans controller axis directions (when axis isn't down anymore)
		if (!axisDown[i].button[CONTROLLER_LEFT_ANALOG_X]) leftAnalogDirX = 0;
		if (!axisDown[i].button[CONTROLLER_LEFT_ANALOG_Y]) leftAnalogDirY = 0;
		if (!axisDown[i].button[CONTROLLER_RIGHT_ANALOG_X]) rightAnalogDirX = 0;
		if (!axisDown[i].button[CONTROLLER_RIGHT_ANALOG_Y]) rightAnalogDirY = 0;
		// axisDown isn't supossed to be clear because we need to store that until the axis is released.
	}
}

void Input::update()
{
	// Get key events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			do_quit = true;
			break;

		case SDL_KEYDOWN:
			//DEBUG WITH : keyToString(event.key.keysym.scancode); printf("down\n");
			if (this->isKeyboardLocked) break;
			// First, check if key isn't alreadly pressed (to avoid repetitive keyPresses while key is down)
			if (!keyDown[event.key.keysym.scancode]) keyPressed[event.key.keysym.scancode] = true;
			keyDown[event.key.keysym.scancode] = true;
			break;

		case SDL_KEYUP:
			//DEBUG WITH : keyToString(event.key.keysym.scancode); printf("released\n");
			if (this->isKeyboardLocked) break;
			keyReleased[event.key.keysym.scancode] = true;
			keyDown[event.key.keysym.scancode] = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			//DEBUG WITH : mouseToString(event.button); printf("down\n");
			if (this->isMouseLocked) break;
			if (!mouseDown[event.button.button]) mousePressed[event.button.button] = true;
			mouseDown[event.button.button] = true;
			break;

		case SDL_MOUSEBUTTONUP:
			//DEBUG WITH : mouseToString(event.button); printf("released\n");
			if (this->isMouseLocked) break;
			mouseReleased[event.button.button] = true;
			mouseDown[event.button.button] = false;
			break;

		case SDL_MOUSEMOTION:
			this->mouseDirX = event.motion.xrel;
			this->mouseDirY = event.motion.yrel;
			this->mouseX = event.motion.x;
			this->mouseY = event.motion.y;
			break;

		/**
		 * This alg has given me a little trouble.
		 * 
		 * Axis are only recognized while in motion, knowing that (and to avoid 
		 * threating SDL_GameControllers outside events), I also placed an interface 
		 * for the axis movement here.
		 * 
		 */
		case SDL_CONTROLLERAXISMOTION:
			// Get controller id
			currController = getControllerID(event.caxis.which);
			if (this->isControllerLocked[currController]) break;
			// The Axis dead zone:
			this->axisDeadZone = AXIS_RANGE * this->sensibility;
			// Check if movement is above the dead zone
			if ((event.caxis.value < -this->axisDeadZone) ||
				(event.caxis.value >  this->axisDeadZone))
			{
				//DEBUG WITH : axisToString(event.caxis);
				if (!axisDown[currController].button[event.caxis.axis]) axisPressed[currController].button[event.caxis.axis] = true;
				axisDown[currController].button[event.caxis.axis] = true;

				/**
				 * Check in which direction it is moving.
				 * 
				 * If the Axis is moving above the positive Dead Zone then it's moving right (1)
				 * or else it's moving left (-1).
				 * 
				 */
				switch (event.caxis.axis) 
				{
				case ControllerAxis::CONTROLLER_LEFT_ANALOG_X:
					this->leftAnalogDirX = (event.caxis.value > this->axisDeadZone) ? 1 : -1;
					break;
				case ControllerAxis::CONTROLLER_LEFT_ANALOG_Y:
					this->leftAnalogDirY = (event.caxis.value > this->axisDeadZone) ? 1 : -1;
					break;
				case ControllerAxis::CONTROLLER_RIGHT_ANALOG_X:
					this->rightAnalogDirX = (event.caxis.value > this->axisDeadZone) ? 1 : -1;
					break;
				case ControllerAxis::CONTROLLER_RIGHT_ANALOG_Y:
					this->rightAnalogDirY = (event.caxis.value > this->axisDeadZone) ? 1 : -1;
					break;
				}
			}
			// Check if Axis was currently down and the movement
			// is below the Dead Zone.
			// If so, it means that the Axis has been released
			// (is back to the 'no capture' zone).
			else if (axisDown[currController].button[event.caxis.axis]) {
				axisReleased[currController].button[event.caxis.axis] = true;
				axisDown[currController].button[event.caxis.axis] = false;
			}
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			//DEBUG WITH : joyToString(event.cbutton); printf("down\n");
			// Get controller id
			currController = getControllerID(event.caxis.which);
			if (this->isControllerLocked[currController]) break;
			if (!joyDown[currController].button[event.cbutton.button]) joyPressed[currController].button[event.cbutton.button] = true;
			joyDown[currController].button[event.cbutton.button] = true;
			break;

		case SDL_CONTROLLERBUTTONUP:
			//DEBUG WITH : joyToString(event.cbutton); printf("released\n");
			// Get controller id
			currController = getControllerID(event.caxis.which);
			if (this->isControllerLocked[currController]) break;
			joyReleased[currController].button[event.cbutton.button] = true;
			joyDown[currController].button[event.cbutton.button] = false;
			break;

		case SDL_CONTROLLERDEVICEADDED:
			openController(event.cdevice.which);
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			currController = getControllerID(event.cdevice.which);
			if (currController < 0) break;	// Unknown controller
			closeController(currController);
			break;

		default:
			break;
		}
	}
}

/***********************************************************************************/
			/*
			 *
			 *						KEYBOARD EVENTS
			 *		  		(KeyboardKey and SDL_Scancode)
			 *
			 */
/***********************************************************************************/
bool Input::isKeyPressed(SDL_Scancode key) { return keyPressed[key]; }
bool Input::isKeyReleased(SDL_Scancode key) { return keyReleased[key]; }
bool Input::isKeyDown(SDL_Scancode key) { return keyDown[key]; }

bool Input::isKeyPressed(KeyboardKey key) 
{
	keyToSDL = (SDL_Scancode)key;
	return keyPressed[keyToSDL];
}
bool Input::isKeyReleased(KeyboardKey key) 
{
	keyToSDL = (SDL_Scancode)key;
	return keyReleased[keyToSDL];
}
bool Input::isKeyDown(KeyboardKey key) 
{
	keyToSDL = (SDL_Scancode)key;
	return keyDown[keyToSDL];
}

/***********************************************************************************/
			/*
			 *
			 *						MOUSE EVENTS
			 *		  (MouseButton and SDL_MouseButtonEvent)
			 *
			 */
/***********************************************************************************/
bool Input::isMousePressed(Uint8 button) { return mousePressed[button]; }
bool Input::isMouseReleased(Uint8 button) {	return mouseReleased[button]; }
bool Input::isMouseDown(Uint8 button) {	return mouseDown[button]; }

bool Input::isMousePressed(MouseButton button) //const
{
	mouseToSDL = (Uint8)button;
	return mousePressed[mouseToSDL];
}
bool Input::isMouseReleased(MouseButton button) //const
{
	mouseToSDL = (Uint8)button;
	return mouseReleased[mouseToSDL];
}
bool Input::isMouseDown(MouseButton button) //const
{
	mouseToSDL = (Uint8)button;
	return mouseDown[mouseToSDL];
}

//Check if mouse is inside box
bool Input::isMouseInside(int x, int y, int w, int h)
{
	//Mouse is left of the box
	if( this->mouseX < x ) { return false; } 
	//Mouse is right of the box 
	else if (this->mouseX > x + w) { return false; }
	//Mouse above the box 
	else if (this->mouseY < y) { return false; }
	//Mouse below the box 
	else if (this->mouseY > y + h) { return false; }

	return true;
}
bool Input::isMouseInside(SDL_Rect* box)
{
	return this->isMouseInside(box->x, box->y, box->w, box->h);
}
/*bool Input::isMouseInside(Shape* s)
{
	return this->isMouseInside(s->box->x, s->box->y, s->box->w, s->box->h);
}*/

bool Input::isMouseMoving() { return (this->mouseDirX != 0 || this->mouseDirY != 0); }
bool Input::isMouseMovingRight() { return (this->mouseDirX > 0); }
bool Input::isMouseMovingLeft() { return (this->mouseDirX < 0); }
bool Input::isMouseMovingUp() { return (this->mouseDirY < 0); }
bool Input::isMouseMovingDown() { return (this->mouseDirY > 0); }

int Input::getMouseX() { return this->mouseX; }
int Input::getMouseY() { return this->mouseY; }

/***********************************************************************************/
		/*
		*
		*					     CONTROLLER EVENTS
		*		  (ControllerButton and SDL_GameControllerButton)
		*
		*/
/***********************************************************************************/
bool Input::isControllerPressed(Uint8 button, int controller) { return joyPressed[controller].button[button]; }
bool Input::isControllerReleased(Uint8 button, int controller) { return joyReleased[controller].button[button]; }
bool Input::isControllerDown(Uint8 button, int controller) { return joyDown[controller].button[button]; }

// For the buttons.
bool Input::isControllerPressed(ControllerButton button, int controller)
{
	joyToSDL = (Uint8)button;
	return joyPressed[controller].button[joyToSDL];
}
bool Input::isControllerReleased(ControllerButton button, int controller)
{
	joyToSDL = (Uint8)button;
	return joyReleased[controller].button[joyToSDL];
}
bool Input::isControllerDown(ControllerButton button, int controller)
{
	joyToSDL = (Uint8)button;
	return joyDown[controller].button[joyToSDL];
}
// For the axis.
bool Input::isControllerPressed(ControllerAxis button, int controller)
{
	axisToSDL = (Uint8)button;
	return axisPressed[controller].button[axisToSDL];
}
bool Input::isControllerReleased(ControllerAxis button, int controller)
{
	axisToSDL = (Uint8)button;
	return axisReleased[controller].button[axisToSDL];
}
bool Input::isControllerDown(ControllerAxis button, int controller)
{
	axisToSDL = (Uint8)button;
	return axisDown[controller].button[axisToSDL];
}

int Input::getNumControllers() { return this->numControllers; }

float Input::getSensibility() { return this->sensibility; }
void Input::setSensibility(float new_sensi) {
	this->sensibility = new_sensi;
	if (new_sensi > 1.0) this->sensibility = 1.0;
	else if (new_sensi < 0) this->sensibility = 0;
}

// Will return -1 if moving left or 1 if moving right, 0 if not moving.
int Input::getLeftAnalogDirX() { return leftAnalogDirX;
/*
		OLD CODE - FOR FUTURE REFERENCE
		int axis_value = SDL_GameControllerGetAxis(controllers[currController], SDL_CONTROLLER_AXIS_LEFTX);
	
		if ((axis_value < -(AXIS_RANGE*this->sensibility)) ||
			(axis_value > (AXIS_RANGE*this->sensibility)))
		{
			// se tiver fora da dead zone entao
			return axis_value > 0 ? 1 : -1;
			// retorna 1 se for positivo ou -1 se for negativo
		}
		// se tiver dentro da dead zone retorna 0
		return 0;
	*/ }
int Input::getRightAnalogDirX() { return rightAnalogDirX; }
// Will return -1 if moving up or 1 if moving down, 0 if not moving.
int Input::getLeftAnalogDirY() { return leftAnalogDirY; }
int Input::getRightAnalogDirY() { return rightAnalogDirY; }

void Input::openController(int id)
{
	// Skip if invalid
	if (!SDL_IsGameController(id))
	{
		printf("Failed to open controller %s\n", SDL_GetError());
		return;
	}
	// Break if opened max num of controllers
	if (numControllers >= MAX_CONTROLLERS)
	{
		printf("Too much controllers, limit reached %i\n", MAX_CONTROLLERS);
		return;
	}
	// Break if controller alreadly opened
	if (id < numControllers)
	{
		printf("Controller %i alreadly added\n", id + 1);
		return;
	}
	// Successfully opened controller
	controllers[numControllers] = SDL_GameControllerOpen(id);
	numControllers++;
	
	// Unlock opened controller
	this->isControllerLocked[id] = false;
	
	//DEBUG WITH : 
	printf("Success opened controler name: %s : num %i / total %i\n", SDL_GameControllerNameForIndex(id), id + 1, SDL_NumJoysticks());
}

void Input::closeController(int id)
{
	if (controllers[id])
	{
		// Close at SDL
		SDL_GameControllerClose(controllers[id]);
		// Kill pointer
		controllers[id] = NULL;
		// Update numControllers
		numControllers--;

		// Clean buttons
		joyPressed[id].button.clear();
		joyReleased[id].button.clear();
		joyDown[id].button.clear();
		axisPressed[id].button.clear();
		axisReleased[id].button.clear();
		axisDown[id].button.clear();

		// Lock closed controller
		this->isControllerLocked[id] = true;

		printf("Closed controller %i / now total %i\n", id + 1, numControllers);
	}
}

int Input::getControllerID(int instance)
{
	SDL_Joystick * j;
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		j = SDL_GameControllerGetJoystick(controllers[i]);
		if (SDL_JoystickInstanceID(j) == instance) {
			// This controller has been removed
			return i;
		}
	}
	return -1;
}

/***********************************************************************************/
		/*
		 *
	     *				LOCKING AND UNLOCKING INPUT
		 *			 (Mouse, Keyboard and Controller)
		 *
		 */
/***********************************************************************************/
void Input::lockInput(InputType peripheral)
{
	switch (peripheral)
	{
	case InputType::KEYBOARD:				this->isKeyboardLocked = true; break;
	case InputType::MOUSE:					this->isMouseLocked = true; break;
	case InputType::CONTROLLER:				for (int i = 0; i < MAX_CONTROLLERS; ++i) { this->isControllerLocked[i] = true; } break;
	case InputType::ALL_INPUTS: default:	this->isKeyboardLocked = true; this->isMouseLocked = true; for (int i = 0; i < MAX_CONTROLLERS; ++i) { this->isControllerLocked[i] = true; } break;
	}
}
void Input::unlockInput(InputType peripheral)
{
		switch (peripheral)
		{
		case InputType::KEYBOARD:				this->isKeyboardLocked = false; break;
		case InputType::MOUSE:					this->isMouseLocked = false; break;
		case InputType::CONTROLLER:				for (int i = 0; i < MAX_CONTROLLERS; ++i) { this->isControllerLocked[i] = false; } break;
		case InputType::ALL_INPUTS: default:	this->isKeyboardLocked = false; this->isMouseLocked = false; for (int i = 0; i < MAX_CONTROLLERS; ++i) { this->isControllerLocked[i] = false; } break;
		}
}
void Input::unlockController(int controller) { this->isControllerLocked[controller] = false; }
bool Input::isLocked(int controller) { return this->isControllerLocked[controller]; }

/***********************************************************************************/
		/*
		 *
	     *						QUITTING GAME
		 *			   (Alt + F4, SDL or Input quit command)
		 *
		 */
/***********************************************************************************/
bool Input::quitRequested()
{
	bool alt_f4 = false;
	if (isKeyPressed(SDL_SCANCODE_F4) &&
		(isKeyPressed(SDL_SCANCODE_RALT) || isKeyPressed(SDL_SCANCODE_LALT))
		)
		alt_f4 = true;

	return (do_quit || alt_f4);
}




/***********************************************************************************/
			/*
			*
			*						CONVERT TO STRING
			*		  	 (All Debug methods for later reference)
			*
			*/
/***********************************************************************************/
void Input::mouseToString(SDL_MouseButtonEvent button)
{
	printf("Mouse %d button %d ('%s')",
		button.which,
		button.button,
		MouseButtonName(button.button));
}

void Input::joyToString(SDL_ControllerButtonEvent button)
{
	printf("Controller %d button %d ('%s') ",
		button.which, button.button,
		ControllerButtonName(button.button));
}

void Input::axisToString(SDL_ControllerAxisEvent axis)
{
	printf("Controller %d axis %d ('%s') value: %d\n",
		axis.which,
		axis.axis,
		ControllerAxisName(axis.axis),
		axis.value);
}

void Input::keyToString(SDL_Scancode key)
{
	// Check if is printable
	if ((key >= SDL_SCANCODE_A) && (key <= SDL_SCANCODE_0))
	{
		const char* a = SDL_GetScancodeName(key);
		printf("key %s\n", a);
	}
}

std::string Input::getKeyString()
{
	for (auto const key : keyPressed)
	{
		if (keyPressed[key.first])
		{
			// Check if is printable
			if ((key.first >= SDL_SCANCODE_A) && (key.first <= SDL_SCANCODE_0))
			{
				std::string a = SDL_GetScancodeName(key.first);
				//printf("key %s\n", a.c_str());
				return a;
			}
		}
	}
	return "";
}

// Controller to String, pode ser util deixar aqui
char* Input::MouseButtonName(const Uint8 button)
{
	switch (button)
	{
#define AXIS_CASE(ax) case SDL_BUTTON_##ax: return #ax
		AXIS_CASE(LEFT);
		AXIS_CASE(MIDDLE);
		AXIS_CASE(RIGHT);
#undef AXIS_CASE
default: return "???";
	}
}

// Controller to String, pode ser util deixar aqui
char* Input::ControllerAxisName(const Uint8 axis)
{
	switch (axis)
	{
#define AXIS_CASE(ax) case SDL_CONTROLLER_AXIS_##ax: return #ax
		AXIS_CASE(INVALID);
		AXIS_CASE(LEFTX);
		AXIS_CASE(LEFTY);
		AXIS_CASE(RIGHTX);
		AXIS_CASE(RIGHTY);
		AXIS_CASE(TRIGGERLEFT);
		AXIS_CASE(TRIGGERRIGHT);
#undef AXIS_CASE
default: return "???";
	}
}

char* Input::ControllerButtonName(const Uint8 button)
{
	switch (button)
	{
#define BUTTON_CASE(btn) case SDL_CONTROLLER_BUTTON_##btn: return #btn
		BUTTON_CASE(INVALID);
		BUTTON_CASE(A);
		BUTTON_CASE(B);
		BUTTON_CASE(X);
		BUTTON_CASE(Y);
		BUTTON_CASE(BACK);
		BUTTON_CASE(GUIDE);
		BUTTON_CASE(START);
		BUTTON_CASE(LEFTSTICK);
		BUTTON_CASE(RIGHTSTICK);
		BUTTON_CASE(LEFTSHOULDER);
		BUTTON_CASE(RIGHTSHOULDER);
		BUTTON_CASE(DPAD_UP);
		BUTTON_CASE(DPAD_DOWN);
		BUTTON_CASE(DPAD_LEFT);
		BUTTON_CASE(DPAD_RIGHT);
#undef BUTTON_CASE
default: return "???";
	}
}

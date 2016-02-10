#include "Input.h"

void Input::init()
{
	this->isKeyboardLocked = false; 
	this->isMouseLocked = false; 
	this->isControllerLocked = false;

	this->mouseX = 0;
	this->mouseY = 0;

	this->do_quit = false;

	// empty for debug purposes only
	printf("Success init input\n");
}

void Input::free()
{
	keyPressed.clear();
	keyReleased.clear();
	keyDown.clear();

	mousePressed.clear();
	mouseReleased.clear();
	mouseDown.clear();

	printf("Success close input\n");
}

// Clear the state of the keys
void Input::clear()
{
	// Limpa os keyPressed e keyReleased
	keyPressed.clear();
	keyReleased.clear();
	// Nao é pra limpar o keyDown pois este deve armazenar os objetos pressionados pra sempre (sic)

	// Limpa os keyPressed e keyReleased
	mousePressed.clear();
	mouseReleased.clear();
	mouseDirX = 0;
	mouseDirY = 0;
	// Nao é pra limpar o keyDown pois este deve armazenar os objetos pressionados pra sempre (sic)
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
			if (this->isKeyboardLocked) break;
			// Verifica primeiro se já nao esta pressionando a tecla (para evitar keyPresses simultaneos com keyDown)
			if (!keyDown[event.key.keysym.scancode]) keyPressed[event.key.keysym.scancode] = true;
			keyDown[event.key.keysym.scancode] = true;
			break;

		case SDL_KEYUP:
			if (this->isKeyboardLocked) break;
			keyReleased[event.key.keysym.scancode] = true;
			keyDown[event.key.keysym.scancode] = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (this->isMouseLocked) break;
			if (!mouseDown[event.button.button]) mousePressed[event.button.button] = true;
			mouseDown[event.button.button] = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (this->isMouseLocked) break;
			mouseReleased[event.button.button] = true;
			mouseDown[event.button.button] = false;
			break;

		case SDL_MOUSEMOTION:
			this->mouseDirX = event.motion.xrel;
			this->mouseDirY = event.motion.yrel;
			break;

		default:
			break;
		}
	}

	//printf("keyDown size: %i\n", keyDown.size());
}

bool Input::isKeyPressed(SDL_Scancode key) //const
{
	return keyPressed[key];
}
bool Input::isKeyReleased(SDL_Scancode key) //const
{
	return keyReleased[key];
}
bool Input::isKeyDown(SDL_Scancode key) //const
{
	return keyDown[key];
	// keyDown não é apagado ao fim de cada interação, na verdade é atribuido o valor "falso" para qualquer tecla já salva
	// Por isso é necessário retornar o estado (V ou F) e não se a chave existe (como nos casos do keyPressed e keyDown)
}

bool Input::isKeyPressed(KeyboardKey key) //const
{
	keyToScanCode = (SDL_Scancode)key;
	return keyPressed[keyToScanCode];
}
bool Input::isKeyReleased(KeyboardKey key) //const
{
	keyToScanCode = (SDL_Scancode)key;
	return keyReleased[keyToScanCode];
}
bool Input::isKeyDown(KeyboardKey key) //const
{
	keyToScanCode = (SDL_Scancode)key;
	return keyDown[keyToScanCode];
}

bool Input::quitRequested()
{
	bool alt_f4 = false;
	if (isKeyPressed(SDL_SCANCODE_F4) &&
		(isKeyPressed(SDL_SCANCODE_RALT) || isKeyPressed(SDL_SCANCODE_LALT))
		)
		alt_f4 = true;

	return (do_quit || alt_f4);
}

/*
FOR PRINTABLE KEYS - TRANSFORMA EM STRING PAR AIMPRIMIR

// Check if a Key is printable
bool InputManager::isPrintable(SDL_Keycode key)
{
return ((key > SDLK_SPACE) && (key < SDLK_z));
}
bool InputManager::isPrintableKeyDown()
{
return (InputManager::isPrintable(this->curPrintableKey));
}
// Makes a printable key internal value -> into a char -> into a string
std::string InputManager::getCurPrintableKey()
{
char c = (char)(this->curPrintableKey);
const char* a = &c;
return (std::string(a));
}

*/

			/*
			 *
			 *						MOUSE EVENTS
			 *		  (MouseButton and SDL_MouseButtonEvent)
			 *
			 */
bool Input::isMousePressed(Uint8 button) //const
{
	return mousePressed[button];
}
bool Input::isMouseReleased(Uint8 button) //const
{
	return mouseReleased[button];
}
bool Input::isMouseDown(Uint8 button) //const
{
	return mouseDown[button];
}
bool Input::isMousePressed(MouseButton button) //const
{
	mouseToButtonCode = (Uint8)button;
	return mousePressed[mouseToButtonCode];
}
bool Input::isMouseReleased(MouseButton button) //const
{
	mouseToButtonCode = (Uint8)button;
	return mouseReleased[mouseToButtonCode];
}
bool Input::isMouseDown(MouseButton button) //const
{
	mouseToButtonCode = (Uint8)button;
	return mouseDown[mouseToButtonCode];
}

bool Input::isMouseInside(int x, int y, int w, int h)
{
	//Check if mouse is inside box 
	int auxX, auxY;
	SDL_GetMouseState(&auxX, &auxY);		// VAI PASSAR ISSO AQUI PRA O SDL EVENT QND FIZER O MOUSEMOTION
	this->mouseX = auxX;
	this->mouseY = auxY;
	
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

// NAO ERA PRA DA ERRO DE PRIVACIDADE UMA VEZ QUE MOUSEX EH PRIVATE?
int Input::getMouseX()
{
	SDL_GetMouseState(&this->mouseX, NULL);
	return this->mouseX;
}
int Input::getMouseY()
{
	SDL_GetMouseState(NULL, &this->mouseY);
	return this->mouseY;
}

		/*
		 *
	     *				LOCKING AND UNLOCKING INPUT
		 *			 (Mouse, Keyboard and Controller)
		 *
		 */
void Input::lockInput(InputType peripheral)
{
	switch (peripheral)
	{
	case InputType::KEYBOARD:				this->isKeyboardLocked = true; break;
	case InputType::MOUSE:					this->isMouseLocked = true; break;
	case InputType::CONTROLLER:				this->isControllerLocked = true; break;
	case InputType::ALL_INPUTS: default:	this->isKeyboardLocked = true; this->isMouseLocked = true; this->isControllerLocked = true; break;
	}
}
void Input::unlockInput(InputType peripheral)
{
	switch (peripheral)
	{
	case InputType::KEYBOARD:				this->isKeyboardLocked = false; break;
	case InputType::MOUSE:					this->isMouseLocked = false; break;
	case InputType::CONTROLLER:				this->isControllerLocked = false; break;
	case InputType::ALL_INPUTS: default:	this->isKeyboardLocked = false; this->isMouseLocked = false; this->isControllerLocked = false; break;
	}
}


/*
	CONTROLLER

	https://davidgow.net/handmadepenguin/ch6.html
	http://blog.5pmcasual.com/game-controller-api-in-sdl2.html
	https://wiki.libsdl.org/SDL_GameControllerOpen?highlight=%28\bCategoryGameController\b%29|%28CategoryEnum%29
	https://wiki.libsdl.org/CategoryGameController

*/
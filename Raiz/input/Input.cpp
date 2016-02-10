#include "Input.h"

void Input::init()
{
	// empty for debug purposes only
	printf("Success init input\n");
}

void Input::free()
{
	keyPressed.clear();
	keyReleased.clear();
	keyDown.clear();
	printf("Success close input\n");
}

// Clear the state of the keys
void Input::clear()
{
	// Limpa os keyPressed e keyReleased
	keyPressed.clear();
	keyReleased.clear();
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
			// Verifica primeiro se já nao esta pressionando a tecla (para evitar keyPresses simultaneos com keyDown)
			if (!keyDown[event.key.keysym.scancode]) keyPressed[event.key.keysym.scancode] = true;
			keyDown[event.key.keysym.scancode] = true;
			break;

		case SDL_KEYUP:
			keyReleased[event.key.keysym.scancode] = true;
			keyDown[event.key.keysym.scancode] = false;
			break;

		default:
			break;
		}
	}

	//printf("keyDown size: %i\n", keyDown.size());
	// Get key states array
	//this->keyboard = SDL_GetKeyboardState(NULL);
}


//bool InputManager::isKeyPressed(KeyboardKey key)
//if (this->isLocked) return false;

bool Input::isKeyPressed(SDL_Scancode key) //const
{
	//return keyboard[key];
	return keyPressed[key];
	// faz um iterator em keyPressed ate o fim (.end) e verifica se a chave existe
	//return keyPressed.find(key) != keyPressed.end();
}

bool Input::isKeyReleased(SDL_Scancode key) //const
{
	return keyReleased[key];
	//return keyReleased.find(key) != keyReleased.end();
}

bool Input::isKeyDown(SDL_Scancode key) //const
{
	return keyDown[key];
	// faz um iterator em keyDown ate o fim (.end) e verifica se a chave é verdadeira ou falsa
	//auto it = keyDown.find(key);
	//return it != keyDown.end() ? it->second : false;
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

/* Using C++ std::map
Init:
mymap['a']="an element";
Use:
std::cout << "mymap['a'] is " << mymap['a'] << '\n';
Prints:
mymap['a'] is an element
*/


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
PARA TRAVAR O TECLADO CASO NECESSARIO NO JOGO

void Input::lockInput()
{
this->isLocked = true;
}
void Input::unlockInput()
{
this->isLocked = false;
}

lockKeyboard()
{
	this->isKeyBoardLocked = true;
}
lockMouse()
{
	this->isMouseLocked = true;
}
...


*/

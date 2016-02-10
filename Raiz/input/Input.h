#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>
#include "InputDefinitions.h"

class Input
{

public:
	void init();
	void free();

	void update();
	void clear();

	// Tells if the keyboard *key* is pressed.
	bool isKeyPressed(SDL_Scancode key);
	// Tells if the keyboard *key* is released.
	bool isKeyReleased(SDL_Scancode key);
	// Tells if the keyboard *key* is currently being pressed.
	bool isKeyDown(SDL_Scancode key);

	// Works both ways, with SDL_Scancode or with KeyboardKey (easier to type)
	bool isKeyPressed(KeyboardKey key);
	bool isKeyReleased(KeyboardKey key);
	bool isKeyDown(KeyboardKey key);

	// Tells if the mouse *button* was pressed just now.
	bool isMousePressed(Uint8 button);
	// Tells if the mouse *button* was released just now.
	bool isMouseReleased(Uint8 button);
	// Tells if the mouse *button* is currently being pressed.
	bool isMouseDown(Uint8 button);
	
	// Works both ways, with SDL_MouseButtonEvent or with MouseButton (easier to type)
	bool isMousePressed(MouseButton button);
	bool isMouseReleased(MouseButton button);
	bool isMouseDown(MouseButton button);

	// Returns the current mouse X position.
	int getMouseX();
	// Returns the current mouse Y position.
	int getMouseY();

	// Tells if the mouse's currently inside the rectangle
	//  specified by #x, #y, #w and #h.
	bool isMouseInside(int x, int y, int w, int h);
	// TO DO
	bool isMouseInside(SDL_Rect* box);
	//bool isMouseInside(Shape* box);
	bool isMouseMoving();
	bool isMouseMovingRight();
	bool isMouseMovingLeft();
	bool isMouseMovingUp();
	bool isMouseMovingDown();

	// Tells if the user asked the game to quit
	// (Alt+F4 or close button).
	bool quitRequested();

	// Calling lockInput and unlockInput will lock/unlock all inputs by default.
	void lockInput(InputType peripheral = InputType::ALL_INPUTS);
	void unlockInput(InputType peripheral = InputType::ALL_INPUTS);
	// To lock/unlock you need to pass a InputType enum: MOUSE, KEYBOARD, CONTROLLER or ALL_INPUTS

private:

	// Saves which keys are currently pressed.
	std::map<SDL_Scancode, bool> keyPressed;
	// Saves which keys are currently released.
	std::map<SDL_Scancode, bool> keyReleased;
	// Saves which keys are currently being pressed down (hold).
	std::map<SDL_Scancode, bool> keyDown;

	// Convertes a KeyboardKey to a SDL_Scancode, based on internal value (decimal, see table)
	SDL_Scancode keyToScanCode;

	std::map<Uint8, bool> mousePressed;
	std::map<Uint8, bool> mouseReleased;
	std::map<Uint8, bool> mouseDown;

	Uint8 mouseToButtonCode;

	bool isKeyboardLocked;
	bool isMouseLocked;
	bool isControllerLocked;

	/// Current mouse X position.
	int  mouseX;
	/// Current mouse Y position.
	int  mouseY;
	/// Relative mouse direction
	int mouseDirX;
	int mouseDirY;

	/// Tells if we must quit the game.
	bool do_quit;
};

#endif
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>
#include "InputDefinitions.h"

/**
 * @brief      Wrapper to manipulate keyboard, mouse and up to 4 (four) controller inputs.
 * 
 * @author     marcelomesmo
 */
class Input
{

public:
	/**
	 * @brief      Init keyboard, mouse and controller inputs. Internal use only, don't call this method.
	 */
	void init();
	/**
	 * @brief      Clear inputs. Internal use only, don't call this method.
	 */
	void free();
	
	/**
	 * @brief      Update input entries. Internal use only, don't call this method.
	 */
	void update();
	/**
	 * @brief      Clear input entries for the next update. Internal use only, don't call this method.
	 */
	void clear();

	/**
	 * @brief      Tells if the keyboard *key* is pressed.
	 *
	 * @param[in]  key   SDL key code.
	 *
	 * @return     True if the key is pressed.
	 */
	bool isKeyPressed(SDL_Scancode key);
	/**
	 * @brief      Tells if the keyboard *key* is released.
	 *
	 * @param[in]  key   SDL key code.
	 *
	 * @return     True if the key is released.
	 */
	bool isKeyReleased(SDL_Scancode key);
	/**
	 * @brief      Tells if the keyboard *key* is currently being pressed.
	 *
	 * @param[in]  key   SDL key code.
	 *
	 * @return     True if the key is currently being pressed.
	 */
	bool isKeyDown(SDL_Scancode key);

	// Works both ways, with SDL_Scancode or with KeyboardKey (easier to type)

	/**
	 * @brief      Tells if the keyboard *key* is pressed.
	 *
	 * @param[in]  key   Key code.
	 *
	 * @return     True if the key is pressed.
	 */
	bool isKeyPressed(KeyboardKey key);
	/**
	 * @brief      Tells if the keyboard *key* is released.
	 *
	 * @param[in]  key   Key code.
	 *
	 * @return     True if the key is released.
	 */
	bool isKeyReleased(KeyboardKey key);
	/**
	 * @brief      Tells if the keyboard *key* is currently being pressed.
	 *
	 * @param[in]  key   Key code.
	 *
	 * @return     True if the key is currently being pressed.
	 */
	bool isKeyDown(KeyboardKey key);


	/**
	 * @brief      Tells if the mouse *button* was pressed.
	 *
	 * @param[in]  key   SDL button code.
	 *
	 * @return     True if the button is pressed.
	 */
	bool isMousePressed(Uint8 button);
	/**
	 * @brief      Tells if the mouse *button* was released.
	 *
	 * @param[in]  key   SDL button code.
	 *
	 * @return     True if the button is released.
	 */
	bool isMouseReleased(Uint8 button);
	/**
	 * @brief      Tells if the mouse *button* is currently being pressed.
	 *
	 * @param[in]  key   SDL button code.
	 *
	 * @return     True if the button is currently being pressed.
	 */
	bool isMouseDown(Uint8 button);
	
	// Works both ways, with SDL_MouseButtonEvent or with MouseButton (easier to type)

	/**
	 * @brief      Tells if the mouse *button* was pressed.
	 *
	 * @param[in]  key   Mouse button code.
	 *
	 * @return     True if the button is pressed.
	 */
	bool isMousePressed(MouseButton button);
	/**
	 * @brief      Tells if the mouse *button* was released.
	 *
	 * @param[in]  key   Mouse button code.
	 *
	 * @return     True if the button is released.
	 */
	bool isMouseReleased(MouseButton button);
	/**
	 * @brief      Tells if the mouse *button* is currently being pressed.
	 *
	 * @param[in]  key   Mouse button code.
	 *
	 * @return     True if the button is currently being pressed.
	 */
	bool isMouseDown(MouseButton button);

	/**
	 * @brief      Returns the current mouse X position.
	 *
	 * @return     Mouse X position relative to screen.
	 */
	int getMouseX();
	/**
	 * @brief      Returns the current mouse Y position.
	 *
	 * @return     Mouse Y position relative to screen.
	 */
	int getMouseY();

	/**
	 * @brief      Tells if the mouse is currently inside the specified
	 *             rectangle.
	 *
	 * @param[in]  x     Rectangle start position X.
	 * @param[in]  y     Rectangle start position Y.
	 * @param[in]  w     Rectangle width.
	 * @param[in]  h     Rectangle height.
	 *
	 * @return     True if the mouse is inside the rectangle.
	 */
	bool isMouseInside(int x, int y, int w, int h);
	/**
	 * @brief      Tells if the mouse is currently inside the specified
	 *             rectangle.
	 *
	 * @param      box   SDL Rectangle.
	 *
	 * @return     True if the mouse is inside the rectangle.
	 */
	bool isMouseInside(SDL_Rect* box);
	/**
	 * @brief      Tells if the mouse is currently inside the specified
	 *             rectangle.
	 *
	 * @param      box   Shape object Rectangle. 
	 *
	 * @return     True if the mouse is inside the rectangle.
	 */
	//bool isMouseInside(Rectangle* box);
	
	/**
	 * @brief      Tells if the mouse is currently moving on screen.
	 *
	 * @return     True if the mouse is moving.
	 */
	bool isMouseMoving();
	// The mouse Dir is wrapped upon these methods so user dont need to check manually
	
	/**
	 * @brief      Tells if the mouse is moving right relative to the screen.
	 *
	 * @return     True if the mouse is moving to the right of the screen.
	 */
	bool isMouseMovingRight();
	/**
	 * @brief      Tells if the mouse is moving left relative to the screen.
	 *
	 * @return     True if the mouse is moving to the left of the screen.
	 */
	bool isMouseMovingLeft();
	/**
	 * @brief      Tells if the mouse is moving up relative to the screen.
	 *
	 * @return     True if the mouse is moving to the top of the screen.
	 */
	bool isMouseMovingUp();
	/**
	 * @brief      Tells if the mouse is moving down relative to the screen.
	 *
	 * @return     True if the mouse is moving to the bottom of the screen.
	 */
	bool isMouseMovingDown();

	/**
	 * @brief      Tells if the controller *button* was pressed.
	 *
	 * @param[in]  button      SDL controller button.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the button is pressed.
	 */
	bool isControllerPressed(Uint8 button, int controller = 0);
	/**
	 * @brief      Tells if the controller *button* was released.
	 *
	 * @param[in]  button      SDL controller button.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the button is released.
	 */
	bool isControllerReleased(Uint8 button, int controller = 0);
	/**
	 * @brief      Tells if the controller *button* is currently being pressed.
	 *
	 * @param[in]  button      SDL controller button.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the button is currently being pressed.
	 */
	bool isControllerDown(Uint8 button, int controller = 0);

	// Works both ways, with SDL_MouseButtonEvent or with MouseButton (easier to type)

	/**
	 * @brief      Tells if the controller *button* was pressed.
	 *
	 * @param[in]  button      Controller button.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the button is pressed.
	 */
	bool isControllerPressed(ControllerButton button, int controller = 0);
	/**
	 * @brief      Tells if the controller *button* was released.
	 *
	 * @param[in]  button      Controller button.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the button is released.
	 */
	bool isControllerReleased(ControllerButton button, int controller = 0);
	/**
	 * @brief      Tells if the controller *button* is currently being pressed.
	 *
	 * @param[in]  button      Controller button.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the button is currently being pressed.
	 */
	bool isControllerDown(ControllerButton button, int controller = 0);
	
	// Works only with ControllerAxis

	/**
	 * @brief      Tells if the controller *axis* was pressed.
	 *
	 * @param[in]  button      Controller axis.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the axis is pressed.
	 */
	bool isControllerPressed(ControllerAxis button, int controller = 0);
	/**
	 * @brief      Tells if the controller *axis* was released.
	 *
	 * @param[in]  button      Controller axis.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the axis is released.
	 */
	bool isControllerReleased(ControllerAxis button, int controller = 0);
	/**
	 * @brief      Tells if the controller *axis* is currently being pressed.
	 *
	 * @param[in]  button      Controller axis.
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if the axis is currently being pressed.
	 */
	bool isControllerDown(ControllerAxis button, int controller = 0);

	/**
	 * @brief      Get total number of open game controllers.
	 *
	 * @return     Number of open controllers.
	 */
	int getNumControllers();
	/**
	 * @brief      Get current game controller axis sensibility.
	 *
	 * @return     A float that varies from 0 (higher sensibility) to 1 (lower sensibility).
	 */
	float getSensibility();
	/**
	 * @brief      Change current game controller axis sensibility.
	 *
	 * @param[in]  new_sensi  { parameter_description }
	 */
	void setSensibility(float new_sensi);

	/**
	 * @brief      Get game controller Left Analog direction X.
	 *
	 * @return     An integer -1 if moving left, 1 if moving right or 0 if not moving.
	 */
	int getLeftAnalogDirX();
	/**
	 * @brief      Get game controller Right Analog direction X.
	 *
	 * @return     An integer -1 if moving left, 1 if moving right or 0 if not moving.
	 */
	int getRightAnalogDirX();
	/**
	 * @brief      Get game controller Left Analog direction Y.
	 *
	 * @return     An integer -1 if moving up, 1 if moving down or 0 if not moving.
	 */
	int getLeftAnalogDirY();
	/**
	 * @brief      Get game controller Right Analog direction Y.
	 *
	 * @return     An integer -1 if moving up, 1 if moving down or 0 if not moving.
	 */
	int getRightAnalogDirY();

	/**
	 * @brief      Check if the user asked the game to quit (Alt+F4 or SDL
	 *             quit). Use as a shortcut.
	 *
	 * @return     True if user pressed Alt+F4 or closed window.
	 */
	bool quitRequested();

	/**
	 * @brief      Lock a game input.
	 *
	 *             Take care while using this since disconnecting/connecting
	 *             controllers will cause to automaticaly lock/unlock the
	 *             controller. Put it preferably inside update functions.
	 *
	 * @param[in]  peripheral  Game input to be locked. Lock all inputs if left
	 *                         empty.
	 */
	void lockInput(InputType peripheral = InputType::ALL_INPUTS);
	/**
	 * @brief      Unlock a game input.
	 *
	 *             Take care while using this since disconnecting/connecting
	 *             controllers will cause to automaticaly lock/unlock the
	 *             controller. Put it preferably inside update functions.
	 *
	 * @param[in]  peripheral  Game input to be unlocked. Unlock all inputs if
	 *                         left empty.
	 */
	void unlockInput(InputType peripheral = InputType::ALL_INPUTS);
	/**
	 * @brief      Unlock only a specific game controller.
	 *
	 * @param[in]  controller  ID of the controller.
	 * 
	 */
	void unlockController(int controller);
	/**
	 * @brief      Check if a specific game controller is locked.
	 *
	 * @param[in]  controller  ID of the controller.
	 *
	 * @return     True if controller is locked.
	 */
	bool isLocked(int controller);

	/**
	 * @brief      Get a String for the the currently pressed key.
	 *
	 * @return     String for the key pressed.
	 */
	std::string getKeyString();

private:

	/**
	 * Saves which keyboard keys are currently being used.
	 */
	std::map<SDL_Scancode, bool> keyPressed;
	std::map<SDL_Scancode, bool> keyReleased;
	std::map<SDL_Scancode, bool> keyDown;

	// Convertes a KeyboardKey to a SDL_Scancode, based on internal value (decimal, see table)
	SDL_Scancode keyToSDL;

	/**
	 * Save which mouse buttons are currently being used.
	 */
	std::map<Uint8, bool> mousePressed;
	std::map<Uint8, bool> mouseReleased;
	std::map<Uint8, bool> mouseDown;

	Uint8 mouseToSDL;

	/**
	 * Save which controller buttons are currently being used.
	 */
	struct joy {
		std::map<Uint8, bool> button;
	} joyPressed[MAX_CONTROLLERS], joyReleased[MAX_CONTROLLERS], joyDown[MAX_CONTROLLERS];
	//std::map<Uint8, bool> joyPressed;
	//std::map<Uint8, bool> joyReleased;
	//std::map<Uint8, bool> joyDown;

	Uint8 joyToSDL;
	
	struct axis {
		std::map<Uint8, bool> button;
	} axisPressed[MAX_CONTROLLERS], axisReleased[MAX_CONTROLLERS], axisDown[MAX_CONTROLLERS];
	// Save which controllers axis are currently being used.
	//std::map<Uint8, bool> axisPressed;
	//std::map<Uint8, bool> axisReleased;
	//std::map<Uint8, bool> axisDown;

	Uint8 axisToSDL;

	// Game Controllers / Pads / Joysticks
	SDL_GameController *controllers[MAX_CONTROLLERS];
	// Num of opened controllers
	int numControllers;
	// CurrController on active EVENT
	int currController;
	// Axis dead zone (AXIS_RANGE * sensibility)
	float axisDeadZone;
	// Axis sensibility (lower numbers will increase sensibility)
	float sensibility;

	bool isKeyboardLocked;
	bool isMouseLocked;
	bool isControllerLocked[MAX_CONTROLLERS];

	/// Current mouse X position.
	int  mouseX;
	/// Current mouse Y position.
	int  mouseY;
	/// Relative mouse directions.
	int mouseDirX;
	int mouseDirY;

	// Relative Left analog directions.
	int leftAnalogDirX;
	int leftAnalogDirY;
	// Relative Right analog directions.
	int rightAnalogDirX;
	int rightAnalogDirY;

	/**
	 * Tells if we must quit the game.
	 */
	bool do_quit;

	/**
	 * @brief      Open a game controller.
	 *
	 * @param[in]  id    The index of the game controller.
	 */
	void openController(int id);
	/**
	 * @brief      Loop through the controllers closing the ones that are
	 *             disconnected.
	 *
	 * @param[in]  id    The index of the game controller.
	 */
	void closeController(int id);
	/**
	 * @brief      Get a game controller ID based on it's instance id.
	 *
	 *             Controller events ADDED returns a ID. Button, Axis and
	 *             REMOVED events returns a instance ID. The instance ID must be
	 *             converted into a valid ID for buttonPressed, buttonReleased
	 *             .. and various other arrays that use the ID to identify the
	 *             controllers.
	 *
	 * @param[in]  instance  The instance id of the game controller.
	 *
	 * @return     The index of the game controller.
	 */
	int getControllerID(int instance);

	//DEBUG WITH :
	void joyToString(SDL_ControllerButtonEvent button);
	void axisToString(SDL_ControllerAxisEvent axis);
	void mouseToString(SDL_MouseButtonEvent button);
	void keyToString(SDL_Scancode key); 
	char* MouseButtonName(const Uint8 button);
	char* ControllerAxisName(const Uint8 axis);
	char* ControllerButtonName(const Uint8 button);
};

#endif
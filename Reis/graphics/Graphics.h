#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "ColorManager.h"

#include "font\Font.h"

/** @enum mapper::Flip
 * @author     marcelomesmo
 * @ingroup    Graphics
 * @brief      A simple strongly typed enum represeting image Flips. Currently 3
 *             (three) types defined inside Graphics.
 */
enum class Flip
{
	NONE = SDL_FLIP_NONE,
	VERTICAL = SDL_FLIP_VERTICAL,
	HORIZONTAL = SDL_FLIP_HORIZONTAL
};

/** @enum mapper::Blend
 * @author     marcelomesmo
 * @ingroup    Graphics
 * @brief      A simple strongly typed enum represeting image Blend. Currently 3
 *             (three) types defined inside Graphics.
 */
enum class Blend
{
	NONE = SDL_BLENDMODE_NONE,
	ADD = SDL_BLENDMODE_ADD,
	BLEND = SDL_BLENDMODE_BLEND,
	MOD = SDL_BLENDMODE_MOD
};

/**
 * @brief      Graphics context used to create game window and rendering.
 * 
 * @author     marcelomesmo
 */
class Graphics
{
public:
	/**
	 * @brief      Init SDL window and renderer.
	 *
	 * @param[in]  title           Game window title.
	 * @param[in]  width           Game window width.
	 * @param[in]  height          Game window height.
	 * @param[in]  set_fullscreen  Set window to full screen.
	 */
	void init(const char* title, int width, int height, bool set_fullscreen);
	/**
	 * @brief      Clear Graphics.
	 */
	void free();

	/**
	 * @brief      Reset to default font and color/bgcolor. Called every state
	 *             change to avoid persistant font and colors.
	 */
	void reset();

	/**
	 * @brief      Begin render Batch. Called every rendering.
	 */
	void begin();
	/**
	 * @brief      End render Batch. Called at the end of every rendering.
	 */
	void end();

	/**
	 * @brief      Draw String.
	 *
	 * @param[in]  x     Start position X.
	 * @param[in]  y     Start position Y.
	 * @param[in]  text  String text.
	 */
	void drawString(int x, int y, std::string text);
	/**
	 * @brief      Draw String with custom Font. Not recommended.
	 *
	 * @param      temp_font  New Font.
	 * @param[in]  x          Start position X.
	 * @param[in]  y          Start position Y.
	 * @param[in]  text       String text.
	 */
	void drawString(Font* temp_font, int x, int y, std::string text);
	/**
	 * @brief      Draw part of String.
	 *
	 * @param[in]  x           Start position X.
	 * @param[in]  y           Start position Y.
	 * @param[in]  text        String text.
	 * @param[in]  startIndex  The index of the first char to draw.
	 * @param[in]  endIndex    The index of the last char to draw.
	 */
	void drawString(int x, int y, std::string text, int startIndex, int endIndex);

	/*	All this drawings are not Anti-aliased. */
	/**
	 * @brief      Draw single pixel.
	 *
	 * @param[in]  x     Draw pixel at position X.
	 * @param[in]  y     Draw pixel at position Y.
	 */
	void drawPixel(int x, int y);
	/**
	 * @brief      Draw a line.
	 *
	 * @param[in]  x1    Start position X.
	 * @param[in]  y1    Start position Y.
	 * @param[in]  x2    End position X.
	 * @param[in]  y2    End position Y.
	 */
	void drawLine(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
	/**
	 * @brief      Draw a rectangle.
	 *
	 * @param[in]  x       Start position X.
	 * @param[in]  y       Start position Y.
	 * @param[in]  width   Rectangle width in pixels.
	 * @param[in]  height  Rectangle height in pixels.
	 * @param[in]  f       Set if Rectangle should be filled (true) or border
	 *                     only (false).
	 */
	void drawRect(int x = 0, int y = 0, int width = 0, int height = 0, bool f = false);
	/**
	 * @brief      Draw a Circle.
	 *
	 * @param[in]  x       Center coordinate X.
	 * @param[in]  y       Center coordinate Y.
	 * @param[in]  radius  Circle radius in pixels.
	 * @param[in]  f       Set if Rectangle should be filled (true) or border
	 *                     only (false).
	 */
	void drawCircle(int x = 0, int y = 0, int radius = 0, bool f = false);
	/**
	 * @brief      Draw a Ellipse.
	 *
	 * @param[in]  x     Center coordinate X.
	 * @param[in]  y     Center coordinate Y.
	 * @param[in]  rx    Ellipse horizontal (X) radius in pixels.
	 * @param[in]  ry    Ellipse vertical (Y) radius in pixels.
	 */
	void drawEllipse(int x, int y, int rx, int ry);
	/**
	 * @brief      Draw a Filled Ellipse.
	 *
	 * @param[in]  x     Center coordinate X.
	 * @param[in]  y     Center coordinate Y.
	 * @param[in]  rx    Ellipse horizontal (X) radius in pixels.
	 * @param[in]  ry    Ellipse vertical (Y) radius in pixels.
	 */
	void drawFilledEllipse(int x, int y, int rx, int ry);

	/**
	 * @brief      Set draw color using Uint8. Use this for new colors.
	 *
	 * @param[in]  red    The red component of the color.
	 * @param[in]  green  The green component of the color.
	 * @param[in]  blue   The blue component of the color.
	 * @param[in]  alpha  The alpha (opt) component of the color.
	 */
	void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);
	/**
	 * @brief      Set draw color using Color class.
	 *
	 * @param[in]  c      Color object.
	 */
	void setColor(Color* c);
	/**
	 * @brief      Set background color using Uint8. Use this for new colors.
	 *             Also changes Shaded TTF Font box color.
	 *
	 * @param[in]  red    The red component of the color.
	 * @param[in]  green  The green component of the color.
	 * @param[in]  blue   The blue component of the color.
	 * @param[in]  alpha  The alpha (opt) component of the color.
	 */
	void setBgColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);
	/**
	 * @brief      Set background color using Color class. Also changes
	 *             Shaded TTF Font box color.
	 *
	 * @param[in]  c      Color object.
	 */
	void setBgColor(Color* c);

	/**
	 * @brief      Get current draw color.
	 *
	 * @return     Color of the current color.
	 */
	Color* getColor();
	/**
	 * @brief      Get current background color.
	 *
	 * @return     Color of the current background color.
	 */
	Color* getBgColor();

	/**
	 * @brief      Set the font to be used when rendering text.
	 *
	 * @param      new_font  The new Font to be used.
	 */
	void setFont(Font* new_font);

	/**
	 * @brief      Get the window Width.
	 *
	 * @return     Current window width in pixels.
	 */
	int getWidth();
	/**
	 * @brief      Get the window Height.
	 *
	 * @return     Current window height in pixels.
	 */
	int getHeight();

	// TODO - Resize Window
	//

	/// Game window renderer.
	static SDL_Renderer* renderer;
private:

	/**
	 * The window we'll be rendering to.
	 */
	SDL_Window* janela;
	//SDL_Renderer* renderer;
	int width;
	int height;

	bool fullscreen;

	/**
	 * The current context draw color.
	 */
	Color* cor;
	/**
	 * The current context background color and Shaded TTF Font box color.
	 */
	Color* bgColor;

	// Auxiliar rect for drawing
	SDL_Rect graphicsBox;

	/**
	 * Globally used font. Standard font is Arial 20.
	 */
	Font* font;
	SDL_Texture* fontTexture;	// Texture to draw font
};

#endif
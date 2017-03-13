#ifndef SPRITE_H
#define SPRITE_H

#include "../Graphics.h"
#include "SpriteSheet.h"

/**
 * @brief      Create a new Sprite image.
 *
 *             Watch out: If you are using images with more than 8-bit rgb the
 *             new libpng version will generate a warning. To remove 'libpng
 *             warning: iCCP: known incorrect sRGB profile' go to:
 *             https://wiki.archlinux.org/index.php/Libpng_errors.
 *
 * @author     marcelomesmo
 */
class Sprite : public Resource
{
public:
	Sprite(std::string path, Color* transparent = Color::Cyan/*, std::string ID = "", std::string type = "ISprite"*/);
	Sprite();
	~Sprite();
	
	/**
	 * @brief      Create a new Sprite object.
	 *
	 *             Load an image from a specified path using background Color
	 *             Key. Uses SDL_Image, which supports BMP, PNM (PPM/PGM/PBM),
	 *             XPM, LBM, PCX, GIF, JPEG, PNG, TGA, and TIFF formats.
	 *
	 * @param[in]  path         Image file path.
	 * @param[in]  transparent  Image Color Key. Usually Color::CYAN or
	 *                          Color::PINK.
	 *
	 * @return     True if loaded successfully.
	 */
	bool create(std::string path, Color* transparent = Color::Cyan);
	/**
	  * @brief      Create a new Sprite object.
	  *
	  *             Load an image from a SpriteSheet's Sprite.
	  *
	  * @param      sheet  SpriteSheet used to get the Sprite.
	  * @param[in]  count  Sprite position in the Sprite Sheet.
	  *
	  * @return     True if loaded successfully.
	  */	
	bool create(SpriteSheet* sheet, int count);
	/**
	 * @brief      Create a new Sprite object.
	 *
	 *             Load an image from a SpriteSheet's Sprite.
	 *
	 * @param      sheet      SpriteSheet used to get the Sprite.
	 * @param[in]  sheetPosX  The X position of the cell on the SpriteSheet.
	 * @param[in]  sheetPosY  The Y position of the cell on the SpriteSheet.
	 *
	 * @return     True if loaded successfully.
	 */
	bool create(SpriteSheet* sheet, int sheetPosX, int sheetPosY);
	/**
	  * @brief      Create a new Sprite object.
	  *
	  *             Load an image from a SpriteSheet's XML. Beware: Internal Use
	  *             Only.
	  *
	  * @param      sheet  SpriteSheet used to get the Sprite.
	  * @param      clip   Sprite clip from the XML.
	  *
	  * @return     True if loaded successfully.
	  */	
	bool create(SpriteSheet* sheet, SDL_Rect* clip);
	/**
	 * @brief      Deallocates Sprite after use.
	 *
	 *             Notice: Take care while using, will also deallocate any
	 *             SpriteSheet referenced by this Sprite.
	 */
	void free();

	/**
	 * @brief      Render Sprite image on screen.
	 *
	 * @param[in]  x        Start position X.
	 * @param[in]  y        Start position Y.
	 * @param[in]  flipped  Flip::HORIZONTAL to draw image flipped on x-axis or
	 *                      Flip::VERTICAL to draw image flipped on y-axis.
	 *                      Flip::NONE by default.
	 */
	void draw(int x, int y, Flip flipped = Flip::NONE);

	/**
	 * @brief      Clip Sprite according to a rectangle inside the image.
	 *
	 * @param[in]  x     Image position X to start clipping.
	 * @param[in]  y     Image position Y to start clipping.
	 * @param[in]  w     Clip width.
	 * @param[in]  h     Clip height.
	 */
	void clip(int x, int y, int w, int h);
	/**
	 * @brief      Clip Sprite according to a rectangle inside the image.
	 *
	 * @param      rect  A Rectangle inside the image.
	 */
	void clip(SDL_Rect* rect);
	/**
	 * @brief      Restore Sprite image to original clipping (full image).
	 */
	void restore();
	
	/**
	 * @brief      Set Color modulation. Default modulation is White.
	 *
	 * @param[in]  red    Red component value to set (from 0 to 255).
	 * @param[in]  green  Green component value to set (from 0 to 255).
	 * @param[in]  blue   Blue component value to set (from 0 to 255).
	 */
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	/**
	 * @brief      Set Color modulation. Default modulation is White.
	 *
	 * @param[in]  c     Color component to set.
	 */
	void setColor(Color* c);

	/**
	 * @brief      Set image Blending.
	 *
	 * @param[in]  blending  Blend enum. Blend::NONE, ADD, BLEND or MOD.
	 */
	void setBlendMode(Blend blending);

	/**
	 * @brief      Set alpha modulation.
	 *
	 * @param[in]  alpha  Alpha value to set (from 0: no transparency to 255:
	 *                    full transparency).
	 */
	void setAlpha(Uint8 alpha);

	/**
	 * @brief      Gets image Width dimension.
	 *
	 * @return     Sprite image Width.
	 */
	int getWidth();
	/**
	 * @brief      Gets image Height dimension.
	 *
	 * @return     Sprite image Height.
	 */
	int getHeight();
	/**
	* @brief      Gets image Anchor X position.
	*
	* @return     Sprite image Anchor X.
	*/
	int getAnchorX();
	/**
	* @brief      Gets image Anchor Y position.
	*
	* @return     Sprite image Anchor Y.
	*/
	int getAnchorY();

	/**
	 * @brief      Set Anchor X position to draw the image.
	 *
	 * @param[in]  x     Anchor X position.
	 */
	void setAnchorX(int x);
	/**
	 * @brief      Set Anchor Y position to draw the image.
	 *
	 * @param[in]  y     Anchor Y position.
	 */
	void setAnchorY(int y);

	/* Vai usar isso quando fizer BITMAP font

	//Pixel manipulators
	bool lockTexture();				// Serve para manipular os pixels da imagem
	bool unlockTexture();			// Atualiza as imagens com os pixels alterados
	void* getPixels();
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);

	//Creates blank texture
	bool createBlank(int w, int h, SDL_TextureAccess access);
	//Set self as render target
	void setAsRenderTarget();
	*/

	// Used for loading a Sprite from SpriteSheet
	SDL_Texture* getImage();
	float getAngle();
	SDL_Rect* getClip();
	//SDL_Point* getCenter();

protected:

	//The actual hardware texture
	SDL_Texture* image;
	void* pixels;
	int pitch;

	//Image dimensions
	int width;
	int height;

	float angle;
	float scaleX;
	float scaleY;

	//Anchor positions
	int anchorX;
	int anchorY;

	/// Which part of the image is printed onscreen.
	//
	//	Normally it's the whole image, but you can clip() it if you like.
	SDL_Rect* clipRect;
	// Auxiliar rect for drawing
	SDL_Rect graphicsBox;

	bool fromSheet;
};

#endif
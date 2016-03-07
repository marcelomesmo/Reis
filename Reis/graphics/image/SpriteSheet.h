#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <vector>
#include "Sprite.h"

/**
 * @brief      Create a new SpriteSheet.
 *
 * @author     marcelomesmo
 */
class SpriteSheet
{
public:
	SpriteSheet(std::string path, int sprite_width, int sprite_height, Color transparent = Color::CYAN);
	SpriteSheet(std::string path, std::string musse_xml_path);
	SpriteSheet();
	/**
	 * @brief      Create a new SpriteSheet in which Sprites have the same size
	 *             (in width and height).
	 *
	 * @param[in]  path           Image file path.
	 * @param[in]  sprite_width   Sprite width in pixels.
	 * @param[in]  sprite_height  Sprite height in pixels.
	 * @param[in]  transparent    Color key transparency.
	 *
	 * @return     True if created successfully.
	 */
	bool create(std::string path, int sprite_width, int sprite_height, Color transparent = Color::CYAN);
	/**
	 * @brief      Create a new SpriteSheet in which Sprites have different
	 *             sizes (in width and height). Read meta-data saved in a Xml
	 *             file.
	 *
	 *             Supports: MuSSE (Multisized SpriteSheet Exporter at
	 *             https://github.com/marcelomesmo/MuSSE).
	 *
	 * @param[in]  path            Image file path.
	 * @param[in]  musse_xml_path  Xml file path.
	 *
	 * @return     True if created successfully.
	 */
	bool create(std::string path, std::string musse_xml_path);

	~SpriteSheet();
	/**
	 * @brief      Deallocates SpriteSheet after use.
	 *
	 *             Notice: Sprites are also deallocated. Any Sprite created from
	 *             this SpriteSheet must be freed before the SpriteSheet.
	 */
	void free();

	/**
	 * @brief      Get a Sprite from the SpriteSheet by its ordered position
	 *             cell in the sheet. Sprites are ordered and counted based on
	 *             the total amount of sprites in that sheet i.e. the tenth
	 *             Sprite in the sheet is counted as Sprite number 10, the
	 *             second is Sprite number 2, etc.
	 *
	 *			   imgs on a sheet	
	 *             0  1  2  3 
	 *             4  5  6	7 
	 *             8  9  10 11 
	 *             sheet ordered count
	 *
	 * @param[in]  count  A ordered count position cell of the Sprite in the
	 *                    sheet based on the total amount of sprites.
	 *
	 * @return     A Sprite from the specified sheet location.
	 */
	Sprite* getSpriteAt(int count);
	/**
	 * @brief      Get a Sprite from the SpriteSheet by its x,y position cell in
	 *             the sheet. Sprites cell is defined as follows:
	 *
	 * 				sheet pos X --->
	 * 				_____________________
	 * 				| 0,0  1,0  2,0  3,0 |   |					0  1  2  3
	 * 				| 0,1  1,1  2,1  3,1 |	 | sheet pos Y		4  5  6	 7
	 * 				|_0,2__1,2__2,2__3,2_|   v				    8  9  10 11
	 *   			imgs on a sheet								sheet ordered count
	 *
	 * @param[in]  sheetPosX  The X position of the cell on the SpriteSheet.
	 * @param[in]  sheetPosY  The Y position of the cell on the SpriteSheet.
	 *
	 * @return     A Sprite from the specified sheet location.
	 */
	Sprite* getSpriteAt(int sheetPosX, int sheetPosY);

	// Pode ser que esses saiam
	// Por enquanto tao sendo usadas como debug apenas
	// Gets a sprite clip on the SpriteSheet (by x,y position)
	SDL_Rect* getSprite(int sheetPosX, int sheetPosY);
	// Gets a sprite clip on the SpriteSheet (by ordered count)
	SDL_Rect* getSprite(int count);
	
	/**
	 * @brief      Get a Sprite clip ordered count position based on the Sprite
	 *             clip x,y position in the sheet.
	 *
	 * @param[in]  sheetPosX  The X position of the cell on the SpriteSheet.
	 * @param[in]  sheetPosY  The Y position of the cell on the SpriteSheet.
	 *
	 * @return     A ordered count position of the Sprite in the sheet.
	 */
	int getSpriteCountByPos(int sheetPosX, int sheetPosY);

	//Sprite& getImage();	
	
	/**
	 * @brief      Return the amount of Sprites on the SpriteSheet.
	 *
	 * @return     Total amount of Sprites in the sheet.
	 */
	int getSpriteCount();
	/**
	 * @brief      Return the amount of horizontal (x-axis) Sprites in the sheet.
	 *
	 * @return     Total amount of Sprites on the x-axis.
	 */
	int getHorizontalCount();
	/**
	 * @brief      Return the amount of vertical (y-axis) Sprites in the sheet.
	 *
	 * @return     Total amount of Sprites on the y-axis.
	 */
	int getVerticalCount();

private:
	Sprite image;

	// Used for fixed size Sprite Sheets
	std::vector<SDL_Rect*> spriteClips;
	int size;
	int columns;
	int lines;

};

#endif
#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <vector>
#include "../Graphics.h"
#include "../../data/xml/MuSSEXmlParser.h"

/**
 * @brief      Create a new SpriteSheet.
 *
 * @author     marcelomesmo
 */
class SpriteSheet
{
public:
	SpriteSheet(std::string path, int sprite_width, int sprite_height, Color transparent = Color::CYAN);
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

	// Get a Sprite clip in x, y position in the SpriteSheet.
	SDL_Rect* getClip(int sheetPosX, int sheetPosY);
	// Get a Sprite clip in count position in the SpriteSheet.
	SDL_Rect* getClip(int count);
	// Check if an Animation exists in the SpriteSheet.
	bool clipExist(std::string name);
	// Get a set of Sprite clips by Animation name from the XML.
	vector<SDL_Rect*> getClip(std::string name);

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
	 * @brief      Get the Sprite Sheet image as a SDL_Texture.
	 *
	 * @return     Spriet Sheet image.
	 */
	SDL_Texture* getImage();

private:
	//The actual hardware texture
	SDL_Texture* image;
	bool initImage(std::string path, Color transparent = Color::CYAN);
	void* pixels;
	int pitch;

	//Image dimensions
	int width;
	int height;

	// Used for fixed size Sprite Sheets
	std::vector<SDL_Rect*> spriteClips;
	// Used for multi size Sprite Sheets (read from XML)
	std::vector<pair<std::string, SDL_Rect*>> spriteClipsFromXml;
	int size;
	int columns;
	int lines;

};

#endif
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(std::string path, int sprite_width, int sprite_height, Color transparent)
{
	create(path, sprite_width, sprite_height);
}
SpriteSheet::SpriteSheet(std::string path, std::string musse_xml_path)
{
	create(path, musse_xml_path);
}
SpriteSheet::SpriteSheet()
{
}

SpriteSheet::~SpriteSheet()
{
}
void SpriteSheet::free()
{
	image.free();
}

	/*
	*		    *************************************	
	*					Creating Sprite Sheet		
	*			*************************************
	*/
// Load Sprite Sheets using Sprites with the same size (in width and height)
bool SpriteSheet::create(std::string path, int sprite_width, int sprite_height, Color transparent)
{
	// Create a Sprite with specified image path
	if(!image.create(path, transparent)) return false;

	/*	
		For SpriteSheets with Sprites that have the same size (in width and height):

		sheet width --->								sheet width --->
		________________					ex: 32x32	___________________
		| 1	   2    3   |   |					imgs	| 0,0  32,0  64,0  |	|
		| 4	   5	6	|	| sheet height				| 0,32 32,32 64,32 |	| sheet height
		|_7____8___imgs_|   v							|_0,64_32,64_64,64_|    v
		imgs on a sheet									img pos on sheet
	*/
	this->lines = 0;
	// Check all lines in the sprite sheet
	for (int j = 0; j < image.getHeight(); j += sprite_height)
	{
		this->columns = 0;
		// Check all columns in the sprite sheet
		for (int i = 0; i < image.getWidth(); i += sprite_width)
		{
			// Get Clip for Sprite in the current position
			SDL_Rect* clip = new SDL_Rect();
			clip->x = i;
			clip->y = j;
			clip->w = sprite_width;
			clip->h = sprite_height;
			//clip = {i, j, sprite_width, sprite_height};
			spriteClips.push_back(clip);

			this->columns++;
		}
		this->lines++;
	}
	// Get how many Sprites we have in the Sprite Sheet (include empty spaces)
	this->size = spriteClips.size();
	printf("Spritesheet %ix%i size: %i\n", lines, columns, size);
	return true;
}

// Load Sprite Sheets using a XML metadata for the Sprites
// Supports: MuSSEXmlParser.
bool SpriteSheet::create(std::string path, std::string musse_xml_path)
{

	return true;
}


/*
*		    *************************************
*					    Getting Sprites
*			*************************************
*/

/*
	Get a sprite (or clip) at a particular cell on the sprite sheet

	int sheetPosX - the X position of the cell on the SpriteSheet
	int sheetPosY - the Y position of the cell on the SpriteSheet

	sheet pos X --->
	_____________________
	| 0,0  1,0  2,0  3,0 |   |					0  1  2  3
	| 0,1  1,1	2,1  3,1 |	 | sheet pos Y		4  5  6	 7
	|_0,2__1,2__2,2__3,2_|   v				    8  9  10 11
	imgs on a sheet								sheet ordered count
*/
SDL_Rect* SpriteSheet::getSprite(int sheetPosX, int sheetPosY)
{
	int count = getSpriteCountByPos(sheetPosX, sheetPosY);
	if (count < 0 || (unsigned)count > spriteClips.size() - 1) {
		printf("invalid sprite frame position %i \n", count);
		return spriteClips[0];
	}
	printf("Pos X: %d Pos Y: %d Width: %d Height: %d \n", spriteClips[count]->x, spriteClips[count]->y, spriteClips[count]->w, spriteClips[count]->h);
	return spriteClips[count];
}
SDL_Rect* SpriteSheet::getSprite(int count)
{
	if (count < 0 || (unsigned)count > spriteClips.size() - 1) {
		printf("invalid sprite frame position %i \n", count);
		return spriteClips[0];
	}
	printf("Pos X: %d Pos Y: %d Width: %d Height: %d \n", spriteClips[count]->x, spriteClips[count]->y, spriteClips[count]->w, spriteClips[count]->h);
	return spriteClips[count];
}
int SpriteSheet::getSpriteCountByPos(int sheetPosX, int sheetPosY)
{
	return sheetPosX + (sheetPosY * columns);
}


Sprite* SpriteSheet::getSpriteAt(int count)
{
	// Check if Sprite position is valid
	if (count < 0 || (unsigned)count > spriteClips.size() - 1) {
		printf("invalid sprite cell position %i \n", count);
		return NULL;
	}
	// Get a reference for this SpriteSheet image.
	Sprite* novo = &image;
	// Define this Sprite's Clip based on the image position in sheet.
	novo->clip(spriteClips[count]);
	// Return the new created Sprite
	return novo;
}
Sprite* SpriteSheet::getSpriteAt(int sheetPosX, int sheetPosY)
{	
	// Check if Sprite position is valid
	int count = getSpriteCountByPos(sheetPosX, sheetPosY);
	if (count < 0 || (unsigned)count > spriteClips.size() - 1) {
		printf("invalid sprite x %i y %i position at cell %i \n", sheetPosX, sheetPosY, count);
		return NULL;
	}
	// Get a reference for this SpriteSheet image.
	Sprite* novo = &image;
	// Define this Sprite's Clip based on the image position in sheet.
	novo->clip(spriteClips[count]);
	// Return the new created Sprite
	return novo;
}

//Sprite& SpriteSheet::getImage(){ return this->image; }

int SpriteSheet::getSpriteCount()
{
	return this->size;
}
int SpriteSheet::getHorizontalCount()
{
	return this->lines;
}
int SpriteSheet::getVerticalCount()
{
	return this->columns;
}
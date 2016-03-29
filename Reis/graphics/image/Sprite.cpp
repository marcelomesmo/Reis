#include "Sprite.h"

Sprite::Sprite(std::string path, Color* transparent)
{
	create(path, transparent);
}
Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	free();
}

// Load Sprite from a Sprite Sheet sprite
bool Sprite::create(SpriteSheet* sheet, int count)
{
	fromSheet = true;

	//Get rid of preexisting texture
	free();
	// Will erase SpriteSheet image if previously assigned

	if (sheet->getImage() == NULL)
	{
		printf("ERROR: Couldn't get Sprite from SpriteSheet.\n");
		return false;
	}

	image = sheet->getImage();
	clipRect = sheet->getClip(count);
	width = clipRect->w;
	height = clipRect->h;

	anchorX = 0;
	anchorY = 0;

	return true;
}

// Load Sprite from a Sprite Sheet sprite with a fixed Clip
bool Sprite::create(SpriteSheet* sheet, SDL_Rect* clip)
{
	fromSheet = true;

	//Get rid of preexisting texture
	free();
	// Will erase SpriteSheet image if previously assigned

	if (sheet->getImage() == NULL)
	{
		printf("ERROR: Couldn't get Sprite from SpriteSheet.\n");
		return false;
	}

	image = sheet->getImage();
	clipRect = clip;
	width = clipRect->w;
	height = clipRect->h;
	
	anchorX = 0;
	anchorY = 0;

	return true;
}

bool Sprite::create(SpriteSheet* sheet, int sheetPosX, int sheetPosY)
{
	fromSheet = true;

	//Get rid of preexisting texture
	free();
	// Will erase SpriteSheet image if previously assigned

	if (sheet->getImage() == NULL)
	{
		printf("ERROR: Couldn't get Sprite from SpriteSheet.\n");
		return false;
	}

	image = sheet->getImage();
	int count = sheet->getSpriteCountByPos(sheetPosX, sheetPosY);
	clipRect = sheet->getClip(count);
	width = clipRect->w;
	height = clipRect->h;

	anchorX = 0;
	anchorY = 0;

	return true;
}

bool Sprite::create(std::string path, Color* transparent)
{
	fromSheet = false;

	//Get rid of preexisting texture
	free();
	// Will erase SpriteSheet image if previously assigned

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("ERROR: Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			printf("ERROR: Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(Graphics::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("ERROR: Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &pixels, &pitch);

				//Copy loaded/formatted surface pixels
				memcpy(pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				width = formattedSurface->w;
				height = formattedSurface->h;

				anchorX = 0;
				anchorY = 0;

				//Get pixel data in editable format
				Uint32* pixs = (Uint32*)pixels;
				int pixelCount = (pitch / 4) * height;

				//Map colors
				SDL_Color colorTransparency = ColorManager::getColor(transparent);
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, colorTransparency.r, colorTransparency.g, colorTransparency.b);
				Uint32 transparency = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixs[i] == colorKey)
					{
						pixs[i] = transparency;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				pixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	//printf("DEBUG: Sucessfully loaded image: %s\n", path.c_str());
	image = newTexture;
	return image != NULL;
}

void Sprite::free()
{
	width = 0;
	height = 0;
	anchorX = 0;
	anchorY = 0;
	pixels = NULL;
	pitch = 0;
	clipRect = NULL;
	angle = 0;

	//Free texture if it exists
	//Clean only if not loaded from a sheet
	if (image != NULL && !fromSheet)
	{
		SDL_DestroyTexture(image);
		image = NULL;
	}
}

void Sprite::draw(int x, int y, Flip flipped)
{
	//Set rendering space and render to screen
	graphicsBox = { x - (((float)anchorX / (float)100) * this->width), y - (((float)anchorY / (float)100) * this->height), this->width, this->height };
	// Will generate a Warning while compiling. Ignore it.

	//Set clip rendering dimensions
	if (this->clipRect != NULL)
	{
		graphicsBox.w = this->clipRect->w;
		graphicsBox.h = this->clipRect->h;
	}

	//Render to screen
	switch (flipped)
	{
	case Flip::HORIZONTAL:			SDL_RenderCopyEx(Graphics::renderer, image, clipRect, &graphicsBox, angle, NULL, SDL_FLIP_HORIZONTAL); break;
	case Flip::VERTICAL:			SDL_RenderCopyEx(Graphics::renderer, image, clipRect, &graphicsBox, angle, NULL, SDL_FLIP_VERTICAL); break;
	case Flip::NONE: default:		SDL_RenderCopyEx(Graphics::renderer, image, clipRect, &graphicsBox, angle, NULL, SDL_FLIP_NONE);
	}
	/*if (flipped) SDL_RenderCopyEx(Graphics::renderer, s->getImage(), s->getClip(), &graphicsBox, s->getAngle(), s->getCenter(), SDL_FLIP_VERTICAL);
	else*/ //SDL_RenderCopyEx(Graphics::renderer, image, clipRect, &graphicsBox, angle, NULL, SDL_FLIP_NONE);
	// adicionar flip horizontal tambem?
	// enum Flip { HORIZONTAL = SDL_FLIP_HORIZONTAL, VERTICAL = SDL_FLIP_VERTICAL, NONE = SDL_FLIP_NONE } 
}

void Sprite::clip(int x, int y, int w, int h)
{
	if (!(this->clipRect))
		this->clipRect = new SDL_Rect();

	// Check if clip is inside the image
	if (x >= 0 && x <= this->width &&
		y >= 0 && y <= this->height &&
		(x + w) <= this->width &&
		(y + h) <= this->height
		)
	{
		this->clipRect->x = x;
		this->clipRect->y = y;
		this->clipRect->w = w;
		this->clipRect->h = h;
	}
	else printf("ERROR: Invalid clip on Sprite: out of bounds.\n");
}
void Sprite::clip(SDL_Rect* rect)
{
	clip(rect->x, rect->y, rect->w, rect->h);
}
void Sprite::restore()
{
	if (!(this->clipRect))
		this->clipRect = new SDL_Rect();

	this->clipRect->x = 0;
	this->clipRect->y = 0;
	this->clipRect->w = this->width;
	this->clipRect->h = this->height;
}

int Sprite::getWidth() { return width; }
int Sprite::getHeight() { return height; }

SDL_Texture* Sprite::getImage() { return image; }
float Sprite::getAngle() { return angle; }
SDL_Rect* Sprite::getClip() { return clipRect; }
//SDL_Point* Sprite::getCenter() { return NULL; }	// TODO

void Sprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(image, red, green, blue);
}
void Sprite::setColor(Color* c)
{
	//SDL_Color cor = ColorManager::getColor(c);
	//Modulate texture rgb
	//SDL_SetTextureColorMod(image, cor.r, cor.g, cor.b);
	SDL_SetTextureColorMod(image, c->r, c->g, c->b);
}

//Set blending
void Sprite::setBlendMode(Blend blending)
{
	//Set blending function
	switch (blending)
	{
	case Blend::ADD:			SDL_SetTextureBlendMode(image, SDL_BLENDMODE_ADD); break;
	case Blend::BLEND:			SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND); break;
	case Blend::MOD:			SDL_SetTextureBlendMode(image, SDL_BLENDMODE_MOD); break;
	case Blend::NONE: default:		SDL_SetTextureBlendMode(image, SDL_BLENDMODE_NONE);
	}
}

//Set alpha modulation
void Sprite::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(image, alpha);
}

void Sprite::setAnchorX(int x) { this->anchorX = x; }
void Sprite::setAnchorY(int y) { this->anchorY = y; }
int Sprite::getAnchorX() { return anchorX; }
int Sprite::getAnchorY() { return anchorY; }
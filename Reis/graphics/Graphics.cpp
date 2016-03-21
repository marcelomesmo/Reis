#include "Graphics.h"

//SDL_Window* janela;
SDL_Renderer* Graphics::renderer;
//TTF_Font* font;

void Graphics::init(const char* title, int width, int height, bool set_fullscreen)
{
	int flags = SDL_WINDOW_SHOWN;

	// initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// testar com full e sem full
	if (set_fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	fullscreen = set_fullscreen;

	/* No Linear Texture Filtering implemented.
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
	*/

	// Create Game Window
	janela = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	// Create screen renderer
	renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
	this->width = width;
	this->height = height;

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//Initialize PNG loading
	IMG_Init(IMG_INIT_PNG);
	//Initialize Font loading
	TTF_Init();

	//Init Default Font
	font = new Font("assets/arial.ttf", 20);

	setColor(Color::WHITE);
	setBgColor(Color::BLACK);

	printf("Success init graphics\n");
}

void Graphics::free()
{
	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if (fullscreen) {
		SDL_SetWindowFullscreen(janela, SDL_FALSE);
	}

	// Clear font texture
	if (fontTexture != NULL)
	{
		SDL_DestroyTexture(fontTexture);
		fontTexture = NULL;
	}
	// Destroy default Font
	font->free();
	delete font;
	font = NULL;

	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(janela);

	// shutdown SDL 
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	printf("Success close graphics\n");
}

void Graphics::reset()
{
	//Init Default Font
	font = new Font("assets/arial.ttf", 20);

	setColor(Color::WHITE);
	setBgColor(Color::BLACK);
}

void Graphics::begin()
{
	//Clear screen
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);
	//printf("Success open batch\n");
}
void Graphics::end()
{
	//Update screen
	SDL_RenderPresent(renderer);
	//printf("Success close batch\n");
}


// Draw String with current font.
void Graphics::drawString(int x, int y, std::string text)
{
	//Get rid of preexisting texture
	if (fontTexture != NULL)
	{
		SDL_DestroyTexture(fontTexture);
		fontTexture = NULL;
	}
	// Has to do this everytime

	//Render text surface
	SDL_Surface* textSurface;

	// Creates a surface based on font render type
	switch (font->getRenderType())
	{
		case Font::RenderType::BLENDED:			textSurface = TTF_RenderText_Blended(font->getFont(), text.c_str(), cor); break;
		case Font::RenderType::SHADED:			textSurface = TTF_RenderText_Shaded(font->getFont(), text.c_str(), cor, bgColor); break;
		case Font::RenderType::SOLID: default:	textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), cor); break;
	}

	//Create texture from surface pixels
	fontTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	//Set rendering space and render to screen
	graphicsBox = { x, y, textSurface->w, textSurface->h };

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	// Sets alpha
	SDL_SetTextureAlphaMod(fontTexture, cor.a);

	//Render to screen
	SDL_RenderCopyEx(renderer, fontTexture, NULL, &graphicsBox, 0.0, NULL, SDL_FLIP_NONE);
}
// Draw String with temporary Font.
void Graphics::drawString(Font* temp_font, int x, int y, std::string text)
{
	//Get rid of preexisting texture
	if (fontTexture != NULL)
	{
		SDL_DestroyTexture(fontTexture);
		fontTexture = NULL;
	}
	// Has to do this everytime

	//Render text surface
	SDL_Surface* textSurface;

	// Creates a surface based on font render type
	switch (temp_font->getRenderType())
	{
	case Font::RenderType::BLENDED:			textSurface = TTF_RenderText_Blended(temp_font->getFont(), text.c_str(), cor); break;
	case Font::RenderType::SHADED:			textSurface = TTF_RenderText_Shaded(temp_font->getFont(), text.c_str(), cor, bgColor); break;
	case Font::RenderType::SOLID: default:	textSurface = TTF_RenderText_Solid(temp_font->getFont(), text.c_str(), cor); break;
	}

	//Create texture from surface pixels
	fontTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	//Set rendering space and render to screen
	graphicsBox = { x, y, textSurface->w, textSurface->h };

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	// Sets alpha
	SDL_SetTextureAlphaMod(fontTexture, cor.a);

	//Render to screen
	SDL_RenderCopyEx(renderer, fontTexture, NULL, &graphicsBox, 0.0, NULL, SDL_FLIP_NONE);
}
// Draw parts of the String
void Graphics::drawString(int x, int y, std::string text, int startIndex, int endIndex)
{
	std::string parted = text.substr(startIndex, endIndex);
	this->drawString(x, y, parted);
}

void Graphics::drawPixel(int x, int y)
{
	SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
	SDL_RenderDrawPoint(renderer, x, y);
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2)
{
	SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

void Graphics::drawRect(int x, int y, int width, int height, bool f)
{
	//Render filled quad
	graphicsBox = { x, y, width, height };

	SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);

	// Filled ou Vazado
	if (f) SDL_RenderFillRect(renderer, &graphicsBox);
	else SDL_RenderDrawRect(renderer, &graphicsBox);

	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

/*
	This methods were taken and adapted from SDL2_gfx library.
*/
void Graphics::drawCircle(int x, int y, int radius, bool f)
{
	if (f) drawFilledEllipse(x, y, radius, radius);
	else drawEllipse(x, y, radius, radius);
}

void Graphics::drawEllipse(int x, int y, int rx, int ry)
{
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph, ypk, ymk;
	int xmi, xpi, ymj, ypj;
	int xmj, xpj, ymi, ypi;
	int xmk, xpk, ymh, yph;

	/*
	* Sanity check radii
	*/
	if ((rx < 0) || (ry < 0)) {
		//return (-1);
		printf("CANT PRINT CIRCLE : RADIUS ERROR");
	}

	/*
	* Special case for rx=0 - draw a vline
	*/
	if (rx == 0) {
		//drawLine(x, y - ry, y + ry, c);
		drawLine(x, y - ry, x, y + ry);
	}
	/*
	* Special case for ry=0 - draw a hline
	*/
	if (ry == 0) {
		//drawLine(x - rx, x + rx, y, c);
		drawLine(x - rx, y, x + rx, y);
	}

	/*
	* Set color
	*/
	//result = 0;
	//result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	//result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Init vars
	*/
	oh = oi = oj = ok = 0xFFFF;

	/*
	* Draw
	*/
	if (rx > ry) {
		ix = 0;
		iy = rx * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if (((ok != k) && (oj != k)) || ((oj != j) && (ok != j)) || (k != j)) {
				xph = x + h;
				xmh = x - h;
				if (k > 0) {
					ypk = y + k;
					ymk = y - k;
					drawPixel(xmh, ypk);
					drawPixel(xph, ypk);
					drawPixel(xmh, ymk);
					drawPixel(xph, ymk);
				}
				else {
					drawPixel(xmh, y);
					drawPixel(xph, y);
				}
				ok = k;
				xpi = x + i;
				xmi = x - i;
				if (j > 0) {
					ypj = y + j;
					ymj = y - j;
					drawPixel(xmi, ypj);
					drawPixel(xpi, ypj);
					drawPixel(xmi, ymj);
					drawPixel(xpi, ymj);
				}
				else {
					drawPixel(xmi, y);
					drawPixel(xpi, y);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;

		} while (i > h);
	}
	else {
		ix = 0;
		iy = ry * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if (((oi != i) && (oh != i)) || ((oh != h) && (oi != h) && (i != h))) {
				xmj = x - j;
				xpj = x + j;
				if (i > 0) {
					ypi = y + i;
					ymi = y - i;
					drawPixel(xmj, ypi);
					drawPixel(xpj, ypi);
					drawPixel(xmj, ymi);
					drawPixel(xpj, ymi);
				}
				else {
					drawPixel(xmj, y);
					drawPixel(xpj, y);
				}
				oi = i;
				xmk = x - k;
				xpk = x + k;
				if (h > 0) {
					yph = y + h;
					ymh = y - h;
					drawPixel(xmk, yph);
					drawPixel(xpk, yph);
					drawPixel(xmk, ymh);
					drawPixel(xpk, ymh);
				}
				else {
					drawPixel(xmk, y);
					drawPixel(xpk, y);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;

		} while (i > h);
	}
}

void Graphics::drawFilledEllipse(int x, int y, int rx, int ry)
{
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph;
	int xmi, xpi;
	int xmj, xpj;
	int xmk, xpk;

	/*
	* Sanity check radii
	*/
	if ((rx < 0) || (ry < 0)) {
		printf("COULDNT DRAW CIRCLE WITH INVALID RADIUS");
	}

	/*
	* Special case for rx=0 - draw a vline
	*/
	if (rx == 0) {
		drawLine(x, y - ry, x, y + ry);
	}
	/*
	* Special case for ry=0 - draw a hline
	*/
	if (ry == 0) {
		drawLine(x - rx, y, x + rx, y);
	}

	/*
	* Set color
	*/
	//result = 0;
	//result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	//result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Init vars
	*/
	oh = oi = oj = ok = 0xFFFF;

	/*
	* Draw
	*/
	if (rx > ry) {
		ix = 0;
		iy = rx * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if ((ok != k) && (oj != k)) {
				xph = x + h;
				xmh = x - h;
				if (k > 0) {
					drawLine(xmh, y + k, xph, y + k);
					drawLine(xmh, y - k, xph, y - k);
				}
				else {
					drawLine(xmh, y, xph, y);
				}
				ok = k;
			}
			if ((oj != j) && (ok != j) && (k != j)) {
				xmi = x - i;
				xpi = x + i;
				if (j > 0) {
					drawLine(xmi, y + j, xpi, y + j);
					drawLine(xmi, y - j, xpi, y - j);
				}
				else {
					drawLine(xmi, y, xpi, y);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;

		} while (i > h);
	}
	else {
		ix = 0;
		iy = ry * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if ((oi != i) && (oh != i)) {
				xmj = x - j;
				xpj = x + j;
				if (i > 0) {
					drawLine(xmj, y + i, xpj, y + i);
					drawLine(xmj, y - i, xpj, y - i);
				}
				else {
					drawLine(xmj, y, xpj, y);
				}
				oi = i;
			}
			if ((oh != h) && (oi != h) && (i != h)) {
				xmk = x - k;
				xpk = x + k;
				if (h > 0) {
					drawLine(xmk, y + h, xpk, y + h);
					drawLine(xmk, y - h, xpk, y - h);
				}
				else {
					drawLine(xmk, y, xpk, y);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;

		} while (i > h);
	}

}

void Graphics::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	cor.r = red;
	cor.g = green;
	cor.b = blue;
	cor.a = alpha;
}

void Graphics::setColor(Color c, Uint8 alpha)
{
	cor.a = alpha;

	switch (c) {
	case Color::WHITE:
		cor.r = 255; cor.g = 255; cor.b = 255;
		break;
	case Color::BLACK:
		cor.r = 0; cor.g = 0; cor.b = 0;
		break;
	case Color::RED:
		cor.r = 255; cor.g = 0; cor.b = 0;
		break;
	case Color::GREEN:
		cor.r = 0; cor.g = 255; cor.b = 0;
		break;
	case Color::BLUE:
		cor.r = 0; cor.g = 0; cor.b = 255;
		break;
	case Color::CYAN:
		cor.r = 0; cor.g = 255; cor.b = 255;
		break;
	case Color::ORANGE:
		cor.r = 255; cor.g = 165; cor.b = 0;
		break;
	case Color::BROWN:
		cor.r = 184; cor.g = 134; cor.b = 11;
		break;
	case Color::YELLOW:
		cor.r = 255; cor.g = 255; cor.b = 0;
		break;
	case Color::PURPLE:
		cor.r = 128; cor.g = 0; cor.b = 128;
		break;
	default:
		printf("Invalid color.");
		break;
	}
}

void Graphics::setColor(SDL_Color c)
{
	this->cor = c;
}

SDL_Color Graphics::getColor()
{
	return this->cor;
}

void Graphics::setBgColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	bgColor.r = red;
	bgColor.g = green;
	bgColor.b = blue;
	bgColor.a = alpha;
}

void Graphics::setBgColor(Color c, Uint8 alpha)
{
	bgColor.a = alpha;

	switch (c) {
	case Color::WHITE:
		bgColor.r = 255; bgColor.g = 255; bgColor.b = 255;
		break;
	case Color::BLACK:
		bgColor.r = 0; bgColor.g = 0; bgColor.b = 0;
		break;
	case Color::RED:
		bgColor.r = 255; bgColor.g = 0; bgColor.b = 0;
		break;
	case Color::GREEN:
		bgColor.r = 0; bgColor.g = 255; bgColor.b = 0;
		break;
	case Color::BLUE:
		bgColor.r = 0; bgColor.g = 0; bgColor.b = 255;
		break;
	case Color::CYAN:
		bgColor.r = 0; bgColor.g = 255; bgColor.b = 255;
		break;
	case Color::ORANGE:
		bgColor.r = 255; bgColor.g = 165; bgColor.b = 0;
		break;
	case Color::BROWN:
		bgColor.r = 184; bgColor.g = 134; bgColor.b = 11;
		break;
	case Color::YELLOW:
		bgColor.r = 255; bgColor.g = 255; bgColor.b = 0;
		break;
	case Color::PURPLE:
		bgColor.r = 128; bgColor.g = 0; bgColor.b = 128;
		break;
	default:
		printf("Invalid bg color.");
		break;
	}
}

void Graphics::setBgColor(SDL_Color c)
{
	this->bgColor = c;
}

SDL_Color Graphics::getBgColor()
{
	return this->bgColor;
}

void Graphics::setFont(Font* new_font)
{
	delete font;
	this->font = new_font;
}

int Graphics::getWidth()
{
	return width;
}

int Graphics::getHeight()
{
	return height;
}
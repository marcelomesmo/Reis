#include "ColorManager.h"

SDL_Color ColorManager::getColor(Color c)
{
	SDL_Color cor;
	switch (c) {
	case Color::WHITE:
		cor = { 255, 255, 255 };
		break;
	case Color::BLACK:
		cor = { 0, 0, 0 };
		break;
	case Color::RED:
		cor = { 255, 0, 0 };
		break;
	case Color::GREEN:
		cor = { 0, 255, 0 };
		break;
	case Color::BLUE:
		cor = { 0, 0, 255 };
		break;
	case Color::CYAN:
		cor = { 0, 255, 255 };
		break;
	case Color::ORANGE:
		cor = { 255, 165, 0 };
		break;
	case Color::BROWN:
		cor = { 184, 134, 11 };
		break;
	case Color::YELLOW:
		cor = { 255, 255, 0 };
		break;
	case Color::PURPLE:
		cor = { 128, 0, 128 };
		break;
	case Color::PINK:
		cor = { 255, 0, 255 };
		break;
	default:
		printf("Invalid Color setting to White.\n");
		cor = { 255, 255, 255 };
		break;
	}
	return cor;
}

#include "ColorManager.h"

SDL_Color ColorManager::getColor(Color* c)
{
	SDL_Color cor;
		cor.r = c->r;
		cor.g = c->g;
		cor.b = c->b;
		cor.a = c->a;
	return cor;
}

Color * ColorManager::getColor(std::string c)
{
	if (c == "Cyan")
	{
		return Color::Cyan;
	}
	else if (c == "Transparent")
	{
		return Color::Transparent;
	}
	else if (c == "White")
	{
		return Color::White;
	}
	else if (c == "Blue")
	{
		return Color::Blue;
	}
	else if (c == "Green")
	{
		return Color::Green;
	}
	else if (c == "Red")
	{
		return Color::Red;
	}
	else if (c == "Black")
	{
		return Color::Black;
	}
	else if (c == "Orange")
	{
		return Color::Orange;
	}
	else if (c == "Brown")
	{
		return Color::Brown;
	}
	else if (c == "Yellow")
	{
		return Color::Yellow;
	}
	else if (c == "Purple")
	{
		return Color::Purple;
	}
	else if (c == "Pink")
	{
		return Color::Pink;
	}
	else
	{
		return Color::Cyan;
	}
}

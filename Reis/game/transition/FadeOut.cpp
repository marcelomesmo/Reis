#include "FadeOut.h"

FadeOut::FadeOut(Color c)
{
	this->setColor(c);
	fadeTime = 500;
	alpha = 0;
}
FadeOut::FadeOut(Color c, Uint32 time)
{
	this->setColor(c);
	fadeTime = time;
	alpha = 0;
}

void FadeOut::update(Game* g, float delta)
{
	// Adds normalized delta (delta*1000) * the increment (maxNum / time).
	alpha += delta * 1000 * (255.0f / fadeTime);
	// Convert float value into Uint8 and saves to SDL_COLOR alpha.
	if (alpha >= 255) cor.a = 255;
	else cor.a = (Uint8) alpha;
}

void FadeOut::preRender(Graphics& g)
{
}
void FadeOut::postRender(Graphics& g)
{
	// DRAWS A COLORED RECT COVERING ALL SCREEN
	SDL_Color old = g.getColor();
	g.setColor(cor);
	g.drawRect(0, 0, g.getWidth(), g.getHeight(), true);
	g.setColor(old);
}

// Fade Out until 255 alpha.
bool FadeOut::isFinished()
{
	return (cor.a >= 255);
}

void FadeOut::setColor(Color c, Uint8 alpha)
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
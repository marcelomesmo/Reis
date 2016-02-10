#include "FadeIn.h"

FadeIn::FadeIn(Color c)
{
	this->setColor(c);
	fadeTime = 500;
	alpha = 255;
}
FadeIn::FadeIn(Color c, Uint32 time)
{
	this->setColor(c);
	fadeTime = time;
	alpha = 255;
}

void FadeIn::update(Game* g, float delta)
{
	// Subtract normalized delta (delta*1000) * the increment (maxNum / time).
	alpha -= delta * 1000 * (255.0f / fadeTime);
	// Convert float value into Uint8 and saves to SDL_COLOR alpha.
	if (alpha <= 0) cor.a = 0;
	else cor.a = (Uint8)alpha;
}

void FadeIn::preRender(Graphics& g)
{
}
void FadeIn::postRender(Graphics& g)
{
	// DRAWS A COLORED RECT COVERING ALL SCREEN
	SDL_Color old = g.getColor();
	g.setColor(cor);
	g.drawRect(0, 0, g.getWidth(), g.getHeight(), true);
	g.setColor(old);
}

// Fade in until <= 0 alpha.
bool FadeIn::isFinished()
{
	return (cor.a <= 0);
}

void FadeIn::setColor(Color c, Uint8 alpha)
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
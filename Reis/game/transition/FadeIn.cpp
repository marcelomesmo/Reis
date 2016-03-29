#include "FadeIn.h"

FadeIn::FadeIn(Color* c)
{
	cor = c;
	cor->a = 255;
	fadeTime = 500;
	alpha = 255;
}
FadeIn::FadeIn(Color* c, Uint32 time)
{
	cor = c;
	cor->a = 255;
	fadeTime = time;
	alpha = 255;
}

void FadeIn::update(Game* g, float delta)
{
	// Subtract normalized delta (delta*1000) * the increment (maxNum / time).
	alpha -= delta * 1000 * (255.0f / fadeTime);
	// Convert float value into Uint8 and saves to SDL_COLOR alpha.
	if (alpha <= 0) cor->a = 0;
	else cor->a = (Uint8)alpha;
}

void FadeIn::preRender(Graphics& g)
{
}
void FadeIn::postRender(Graphics& g)
{
	// DRAWS A COLORED RECT COVERING ALL SCREEN
	Color* old = g.getColor();
	g.setColor(cor);
	g.drawRect(0, 0, g.getWidth(), g.getHeight(), true);
	g.setColor(old);
}

// Fade in until <= 0 alpha.
bool FadeIn::isFinished()
{
	return (cor->a <= 0);
}
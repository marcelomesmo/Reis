#include "FadeOut.h"

FadeOut::FadeOut(Color* c)
{
	cor = c;
	cor->a = 0;
	fadeTime = 500;
	alpha = 0;
}
FadeOut::FadeOut(Color* c, Uint32 time)
{
	cor = c;
	cor->a = 0;
	fadeTime = time;
	alpha = 0;
}

void FadeOut::update(Game* g, float delta)
{
	// Adds normalized delta (delta*1000) * the increment (maxNum / time).
	alpha += delta * 1000 * (255.0f / fadeTime);
	// Convert float value into Uint8 and saves to SDL_COLOR alpha.
	if (alpha >= 255) cor->a = 255;
	else cor->a = (Uint8) alpha;
}

void FadeOut::preRender(Graphics& g)
{
}
void FadeOut::postRender(Graphics& g)
{
	// DRAWS A COLORED RECT COVERING ALL SCREEN
	Color* old = g.getColor();
	g.setColor(cor);
	g.drawRect(0, 0, g.getWidth(), g.getHeight(), true);
	g.setColor(old);
}

// Fade Out until 255 alpha.
bool FadeOut::isFinished()
{
	return (cor->a >= 255);
}
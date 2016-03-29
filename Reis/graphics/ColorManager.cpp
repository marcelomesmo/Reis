#include "ColorManager.h"

SDL_Color ColorManager::getColor(Color* c)
{
	SDL_Color cor = {c->r, c->g, c->b, c->a};
		/*cor.r = c->r;
		cor.g = c->g;
		cor.b = c->b;
		cor.a = c->a;*/
	return cor;
}

#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include <SDL.h>
#include <stdio.h>
#include "Color.h"

/** @namespace ColorManager
 * @author     marcelomesmo
 * @ingroup    Graphics
 * @brief      A namespace for Color Management.
 */
namespace ColorManager
{
	/**
	 * @brief      Convert a Reis' Color to a SDL_Color.
	 *
	 * @param[in]  c     Color object.
	 *
	 * @return     Return a SDL_Color corresponding to the Color parameter.
	 */
	SDL_Color getColor(Color* c);
}

#endif

/*
Reis Game Engine
Copyright (C) 2015-2016 Marcelo de Barros <marcelo.barbosa@ifrn.edu.br>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
*/

/**
*  \file Reis.h
*  \author	marcelomesmo
*
*  Main include header for the Raiz Game Engine.
*/
#ifndef _REIS_H
#define _REIS_H

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib") 
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib") 
#pragma comment(lib, "SDL2_mixer.lib") 

#include "game\Game.h"
#include "game\Scene.h"
#include "data\Timer.h"
#include "graphics\Graphics.h"
#include "graphics\Color.h"
#include "graphics\ColorManager.h"
#include "graphics\font\Font.h"
#include "graphics\image\Sprite.h"
#include "graphics\image\SpriteSheet.h"
#include "graphics\image\Animation.h"
#include "data\xml\MuSSEXmlParser.h"
#include "data\xml\rapidxml\rapidxml.hpp"
#include "data\xml\rapidxml\rapidxml_utils.hpp"
//#include "data\xml\rapidxml\rapidxml_print.hpp"
//#include "data\xml\rapidxml\rapidxml_iterators.hpp"
#include "game\transition\Transition.h"
#include "game\transition\FadeIn.h"
#include "game\transition\FadeOut.h"
#include "input\InputDefinitions.h"
#include "input\Input.h"

#endif
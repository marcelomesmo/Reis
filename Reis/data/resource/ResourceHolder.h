#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include "../../graphics/image/Animation.h"
// Animation includes Sprite includes SpriteSheet includes Resource

using SpriteList = std::vector<std::pair<Sprite*, std::string>>;
using SpriteSheetList = std::vector<std::pair<SpriteSheet*, std::string>>;
using AnimationList = std::vector<std::pair<Animation*, std::string>>;
//typedef std::vector<std::pair<Resource, std::string>> ResourceList;

/**
* @brief      Container for Resources.
* 
* 				Maintain lists for: Sprites, SpriteSheet, Animation, 
* 				
* 				Dependency for ResourceManager.
* 				Dependency for ResourceManagerParser.
*
* @author     marcelomesmo
*/
struct ResourceHolder
{
	SpriteList listaSprites;
	SpriteSheetList listaSpriteSheet;
	AnimationList listaAnimation;
};

#endif
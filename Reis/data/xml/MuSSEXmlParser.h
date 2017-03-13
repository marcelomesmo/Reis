#ifndef MUSSEXMLPARSER_H
#define MUSSEXMLPARSER_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
using namespace rapidxml;

#include <vector>
#include <iostream>
#include <sstream>

#include <SDL.h>

#include "..\..\graphics\Color.h"

/**
 * @brief      XMLParser in C++ to read MuSSE's XML files.
 *
 * @author     marcelomesmo
 */
class MuSSEXmlParser
{
public:
	/**
	 * @brief      Open the XML file to parse.
	 *
	 * @param[in]  src   XML file path.
	 *
	 * @return     True if loaded successfully.
	 */
	bool parseXmlFile(const char src[]);

	/**
	 * @brief      Get the name and clips for Animations in the XML.
	 *
	 * @return     A vector containing all the Sprites meta-data organized by:
	 *             animation_name, sprite_clip.
	 */
	std::vector<std::pair<std::string, SDL_Rect*>> getClips();
	//std::vector<Sprite_XML> getClips();
	/* struct Sprite_XML{
		std::string anim_name;
		SDL_Rect* clip;
		Point anchor;
	};
	em cima da funcao
	*/
	
	/**
	 * @brief      Get the SpriteSheet image path.
	 *
	 * @return     Path name of the SpriteSheet image.
	 */
	std::string getName();
	/**
	 * @brief      Get the SpriteSheet color key value.
	 *
	 * @return     Color key object.
	 */
	Color* getColorKey();

private:
	std::stringstream buffer;
	std::string content;
	// XML document to be parsed
	xml_document<> doc;
	xml_node<> *spritesheet;
	xml_node<> *animations;

	std::string sheet_name;
	Color* colorkey;
	int width, height;

};

#endif
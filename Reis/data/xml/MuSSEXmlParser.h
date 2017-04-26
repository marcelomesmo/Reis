#ifndef MUSSEXMLPARSER_H
#define MUSSEXMLPARSER_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
using namespace rapidxml;

#include <sstream>
#include <vector>
#include <iostream>

#include <SDL.h>

#include "../../graphics/Color.h"

struct Sprite_Xml
{
	std::string name;
	SDL_Rect* clip;
	int ancX;
	int ancY;
};

/**
 * @brief      XMLParser in C++ to read MuSSE's XML files. Work as ResourceManager for MuSSE files.
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
	 * @brief      Get all meta-data for sprites in the xml using an Animation name.
	 *
	 * @param[in]  name  Animation name.
	 *
	 * @return     True if loaded successfully.
	 */
	std::vector<Sprite_Xml> getSpritesData(std::string name);
	
	/**
	 * @brief      Check if an Animation exist in xml.
	 *
	 * @param[in]  name  Animation name.
	 *
	 * @return     True if Animation exist.
	 */
	bool hasAnimation(std::string name);

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
		std::string sheet_name;
		Color* colorkey;
		int width, height;
	
	xml_node<> *animations;
};

#endif
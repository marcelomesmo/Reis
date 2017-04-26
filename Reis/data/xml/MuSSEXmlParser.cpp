#include "MuSSEXmlParser.h"

bool MuSSEXmlParser::parseXmlFile(const char src[])
{
	std::ifstream file(src);
	buffer << file.rdbuf();
	file.close();
	content = buffer.str();
	if (content.size() == 0)
	{
		std::cout << "ERROR: [MUSSEParser::parse] Failed to load XML src file.\n";
		return false;
	}

	doc.parse<0>(&content[0]);

	spritesheet = doc.first_node();

	if (spritesheet->first_attribute("image_name") == 0 ||
		spritesheet->first_attribute("width") == 0 ||
		spritesheet->first_attribute("height") == 0)
	{
		std::cout << "ERROR: [MUSSEParser::parse] Image name, width or height not found in file [" << spritesheet->name() << "].\n";
		return false;
	}
	if (spritesheet->first_attribute("ck_r") == 0 ||
		spritesheet->first_attribute("ck_g") == 0 ||
		spritesheet->first_attribute("ck_b") == 0)
	{
		std::cout << "ERROR: [MUSSEParser::parse] Colorkey values not found in file [" << spritesheet->name() << "].\n";
		return false;
	}

	this->sheet_name = spritesheet->first_attribute("image_name")->value();
	this->width = atoi( spritesheet->first_attribute("width")->value() );
	this->height = atoi( spritesheet->first_attribute("height")->value() );
	int r = atoi( spritesheet->first_attribute("ck_r")->value() );
	int g = atoi( spritesheet->first_attribute("ck_g")->value() );
	int b = atoi( spritesheet->first_attribute("ck_b")->value() );
	this->colorkey = new Color(r, g, b);

	// Get a list of Animation elements
	animations = spritesheet->first_node("animation");

	return true;
}

std::vector<Sprite_Xml> MuSSEXmlParser::getSpritesData(std::string name)
{
	std::string anim_name;
	// Inside each animation we have a vector of sprites with : posX, posY, w, h, anchorX, anchorY and name of each sprite
	xml_node<>* spriteList;
		std::string sprite_name;
		int posX, posY, w, h, ancX, ancY;
		SDL_Rect* clip;
	
	std::vector<Sprite_Xml> sprites;

	xml_node<>* animList = animations;
	
	// Iterate a List of Animation elements
	for (animList; animList; animList = animList->next_sibling())
	{
		if (animList->first_attribute("name") == 0 )
		{
			std::cout << "ERROR: [MUSSEParser::getSprites] Animation name not found in file [" << spritesheet->name() << "].\n";
			break;
		}
		anim_name = animList->first_attribute()->value();

		if (anim_name == name)
		{
			// Get a NodeList of Sprite elements for that animation
			spriteList = animList->first_node("sprite");

			// For each Sprite
			for (spriteList; spriteList; spriteList = spriteList->next_sibling())
			{

				// Create Animation (using name duration) from MuSSE 
				if (spriteList->first_attribute("name") == 0)
				{
					std::cout << "ERROR: [MUSSEParser::getSprites] Sprite name not found in file [" << spritesheet->name() << "] for anim [" << anim_name << "].\n";
					break;
				}

				if( spriteList->first_node("offset_x") == 0 || spriteList->first_node("offset_y") == 0 ||
					spriteList->first_node("width") == 0 || spriteList->first_node("height") == 0 ||
					spriteList->first_node("anchor_x") == 0 || spriteList->first_node("anchor_y") == 0)
				{
					std::cout << "ERROR: [MuSSEParser::getSprites] Sprite offset_x, offset_y, width, height, anchor_x or anchor_y not found in file [" << spritesheet->name() << "] for anim [" << anim_name << "].\n";
					break;
				}

				Sprite_Xml novo;
				// Get Sprite name, position and size
				sprite_name = spriteList->first_attribute()->value();
				posX = std::stoi(spriteList->first_node("offset_x")->value());
				posY = std::stoi(spriteList->first_node("offset_y")->value());
				w = std::stoi(spriteList->first_node("width")->value());
				h = std::stoi(spriteList->first_node("height")->value());
				ancX = std::stoi(spriteList->first_node("anchor_x")->value());
				ancY = std::stoi(spriteList->first_node("anchor_y")->value());

				// sprite = new Sprite(sprite_name, posX, posY, w, h, ancX, ancY);
				clip = new SDL_Rect({ posX, posY, w, h });

				novo.name = sprite_name;
				novo.clip = clip;
				novo.ancX = ancX;
				novo.ancY = ancY;

				sprites.push_back(novo);
			}

			return sprites;
		}
	}
	return sprites;
}

// Check if a Animation exist in xml.
bool MuSSEXmlParser::hasAnimation(std::string name)
{
	std::string anim_name;
	xml_node<>* animList = animations;

	// Iterate a List of Animation elements
	for (animList; animList; animList = animList->next_sibling())
	{
		anim_name = animList->first_attribute()->value();
		
		if (anim_name == name)
		{
			return true;
		}
	}
	return false;
}

std::string MuSSEXmlParser::getName() { return this->sheet_name; }
Color* MuSSEXmlParser::getColorKey() { return this->colorkey; }
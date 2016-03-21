#include "MuSSEXmlParser.h"

bool MuSSEXmlParser::parseXmlFile(const char src[])
{
	// Creates a rapidxml::File to read Files
	//file<> xmlFile(src); // Default template is char
	// Parse new document using a RapidXml representation of the XML file
	// doc.parse<0>(xmlFile.data());

	// (above code) Has been replaced by:

	// New code
	std::ifstream file(src);
	buffer << file.rdbuf();
	file.close();
	content = buffer.str();
	if (content.size() == 0)
	{
		printf("ERROR: Failed to load src file.\n");
		return false;
	}

	doc.parse<0>(&content[0]);
	// This is done to keep a outside file saved. So we can split into 2 different methods. 
	// (above solution is more elegant but was causing file to be erased after method end)

	// Get SpriteSheet element
	spritesheet = doc.first_node();

	//cout << "DEBUG: Root element : " << spritesheet->name() << "\n";
	//cout << "----------------------------" << "\n";

	this->sheet_name = spritesheet->name();
	// this->sheet_path = ?
	// this->color_key = ?

	// Get a list of Animation elements
	animations = spritesheet->first_node("animation");

	return true;
}

std::vector<pair<std::string, SDL_Rect*>> MuSSEXmlParser::getClips()
{
	// A vector with animation names and clips
	std::vector<pair<std::string, SDL_Rect*>> novo;

	std::string anim_name;
		// Inside each animation we have a vector of sprites with : posX, posY, w, h, clip and name of each sprite
		xml_node<>* sprites; 
			std::string sprite_name;
			int posX, posY, w, h;
			SDL_Rect* clip;

	// Iterate a List of Animation elements
	for (animations; animations; animations = animations->next_sibling())
	{
		// cout << "DEBUG: Current element : " << animations->first_attribute()->value() << "\n";
		anim_name = animations->first_attribute()->value();

			// Get a NodeList of Sprite elements
			sprites = animations->first_node("sprite");

			// For each Sprite
			for (sprites; sprites; sprites = sprites->next_sibling())
			{
				// Get Sprite name, position and size
				sprite_name = sprites->first_attribute()->value();
				posX = std::stoi(sprites->first_node("offset_x")->value());
				posY = std::stoi(sprites->first_node("offset_y")->value());
				w = std::stoi(sprites->first_node("width")->value());
				h = std::stoi(sprites->first_node("height")->value());

				clip = new SDL_Rect({ posX, posY, w, h });

				novo.push_back({ anim_name, clip });
			}
	}

	return novo;
}

std::string MuSSEXmlParser::getName() { return this->sheet_name; }
//std::string MuSSEXmlParser::getPath() { return this->sheet_path; }
//Color MuSSEXmlParser::getColorKey() { return this->; }
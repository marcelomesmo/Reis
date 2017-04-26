#include "ResourceManagerParser.h"

bool ResourceManagerParser::parseXmlFile(const char src[])
{
	std::ifstream file(src);
	buffer << file.rdbuf();
	file.close();
	content = buffer.str();
	if (content.size() == 0)
	{
		std::cout << "ERROR: [RMParser::parse] Failed to load XML src file.\n";
		return false;
	}

	doc.parse<0>(&content[0]);

	assets = doc.first_node();

	if (assets->first_attribute("pack") == 0)
	{
		std::cout << "ERROR: [RMParser::parse] Pack name not found in file [" << assets->name() << "].\n";
		return false;
	}

	this->pack_name = assets->first_attribute("pack")->value();

	// Get a list of Scene elements
	scenes = assets->first_node("scene");

	// No resource loaded
	this->currentID = "";

	return true;
}

bool ResourceManagerParser::getResourcesData(std::string scene)
{
	std::pair<std::string, xml_node<>*> novo;
	std::string scene_name;

	// Check if alreadly loaded
	for (std::pair<std::string, xml_node<>*> r : resources)
	{
		if (r.first == scene)
		{
			std::cout << "WARNING: Scene [" << scene_name << "] alreadly loaded." << std::endl;
			return true;
		}
	}

	// Iterate a List of Scene elements
	for (scenes; scenes; scenes = scenes->next_sibling())
	{
		scene_name = scenes->first_attribute()->value();

		if(scene_name == scene)
		{

			// Get a NodeList of Resource elements for the scene
			novo.first = scene_name;
			novo.second = scenes->first_node("resource");

			resources.push_back(novo);

			return true;
		}
	}
	return false;
}

int ResourceManagerParser::getResourcesCount(std::string scene)
{
	int total = 0;

	for (std::pair<std::string, xml_node<>*> r : resources)
	{
		// Find scene
		if (r.first == scene) {
			xml_node<>* novo = r.second;
			// Count how many resources for the scene
			for (novo; novo; novo = novo->next_sibling()) { total++; }
			return total;
		}
	}

	return total;
}

int ResourceManagerParser::getResourcesCount()
{
	int total = 0;

	for (std::pair<std::string, xml_node<>*> r : resources)
	{
		// Count how many resources in all scenes
		xml_node<>* novo = r.second;
		for (novo; novo; novo = novo->next_sibling()) { total++; }
	}

	return total;
}

// Do:
// 	this->resources.size();
// For total of scenes init.

bool ResourceManagerParser::loadNext(ResourceHolder & holder, std::string scene, int current)
{
	std::string id, type, path;

	for (std::pair < std::string, xml_node<>*> r : resources)
	{
		// Find the scene
		if(r.first == scene) 
		{
			// Skip alreadly loaded resources
			int skip = 0;
			for (r.second; r.second; r.second = r.second->next_sibling())
			{
				if(skip == current)
				{
					// Exception for missing id, type or path
					if (r.second->first_attribute("id") == 0 || r.second->first_attribute("type") == 0
						|| r.second->first_attribute("path") == 0)
					{
						std::cout << "ERROR: [RMParser::Load] Missing values for id, type or path for scene [" << scene << "]" << std::endl;
						return false;
					}

					// Get Resource id, type and path
					id = r.second->first_attribute("id")->value();
					type = r.second->first_attribute("type")->value();
					path = r.second->first_attribute("path")->value();
					
					// case Sprite (using image):
					if (type == "ISprite") {
						Sprite* s = new Sprite();

						std::string c_key = "Cyan";
						// Checking missing values
						if (r.second->first_node("c_key") != 0)
						{

							std::string c_k = r.second->first_node("c_key")->value();
							// Exception for missing value
							if (c_k.empty())
							{
								std::cout << "ERROR: [RMParser::Load] Missing values for color_key of ";
								std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
								delete s;
								return false;
							}

							c_key = c_k;
						}

						if (!s->create(path, ColorManager::getColor(c_key)))
						{
							std::cout << "ERROR: [RMParser::Load] Couldn't create ISprite for scene [" << scene << "]" << std::endl;
							delete s;
							return false;
						}

						s->setResourceID(id);
						s->setResourceFilePath(path);
						s->setResourceType(type);

						// Add resource to the list
						holder.listaSprites.push_back({ s, scene });

						// Found the resource, finish
						
						// Save last loaded resource ID
						currentID = id;
						return true;
					}
					// case SpriteSheet:
					else if (type == "SpriteSheet") {
						SpriteSheet* s = new SpriteSheet();

						// Create SpriteSheet using: Path Width Height
						if (r.second->first_node("sprite_width") != 0 && r.second->first_node("sprite_height") != 0)
						{
							std::string s_w = r.second->first_node("sprite_width")->value();
							std::string s_h = r.second->first_node("sprite_height")->value();
							// Exception for missing values
							if ( s_w.empty() || s_h.empty())
							{
								std::cout << "ERROR: [RMParser::Load] Missing values for sprite_width or sprite_height of ";
								std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
								delete s;
								return false;
							}

							int sprite_width = std::stoi(s_w);	// Convert to int
							int sprite_height = std::stoi(s_h);	// Convert to int

							std::string c_key = "Cyan";
							if (r.second->first_node("c_key") != 0)
							{

								std::string c_k = r.second->first_node("c_key")->value();
								// Exception for missing value
								if (c_k.empty())
								{
									std::cout << "ERROR: [RMParser::Load] Missing values for color_key of ";
									std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
									delete s;
									return false;
								}

								c_key = c_k;
							}

							if (!s->create(path, sprite_width, sprite_height, ColorManager::getColor(c_key)))
							{
								std::cout << "ERROR: [RMParser::Load] Couldn't create SpriteSheet [" << id << "] for scene [" << scene << "]" << std::endl;
								delete s;
								return false;
							}
						}
						// Create SpriteSheet using: Path MuSSE_XML
						else if (r.second->first_node("musse_xml") != 0)
						{
							std::string musse_xml = r.second->first_node("musse_xml")->value();
							
							// Exception for missing values
							if (musse_xml.empty())
							{
								std::cout << "ERROR: [RMParser::Load] Missing values for musse_xml of ";
								std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
								delete s;
								return false;
							}

							if (!s->create(path, musse_xml))
							{
								std::cout << "ERROR: [RMParser::Load] Couldn't create SpriteSheet [" << id << "] with musse xml [" << musse_xml << "] for scene [" << scene << "]" << std::endl;
								delete s;
								return false;
							}
						}
						else
						{
							std::cout << "ERROR: [RMParser::Load] Couldn't create SpriteSheet [" << id << "] for scene [" << scene << "]. Invalid attributes in xml pack [" << pack_name << "]" << std::endl;
							delete s;
							return false;
						}

						s->setResourceID(id);
						s->setResourceFilePath(path);
						s->setResourceType(type);

						// Everything is Ok. Add resource in list.
						holder.listaSpriteSheet.push_back({ s, scene });

						// Found the resource, finish
						
						// Save last loaded ID
						currentID = id; 
						return true;
					}
					// case Sprite (using SpriteSheet):
					else if (type == "Sprite") 
					{
						Sprite* s = new Sprite();

						// Check if SpriteSheet is valid and alreadly initiated.
						for (std::pair<SpriteSheet *, std::string> findSheet : holder.listaSpriteSheet)
						{
							// SpriteSheet found
							if (findSheet.first->getResourceID() == path)
							{
								// Create Sprite using sheetPosX sheetPosY
								if (r.second->first_node("sheet_pos_X") != 0 && r.second->first_node("sheet_pos_Y") != 0)
								{
									std::string pX = r.second->first_node("sheet_pos_X")->value();
									std::string pY = r.second->first_node("sheet_pos_Y")->value();
									// Exception for missing values
									if (pX.empty() || pY.empty())
									{
										std::cout << "ERROR: [RMParser::Load] Missing values for sheet_pos_X or sheet_pos_Y of ";
										std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
										delete s;
										return false;
									}

									int spritePosX = std::stoi(pX);
									int spritePosY = std::stoi(pY);

									if (!s->create(findSheet.first, spritePosX, spritePosY))
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Sprite for scene [" << scene << "] ";
										std::cout << "using pos X [" << spritePosX << "] posY [" << spritePosY << "]" << std::endl;
										delete s;
										return false;
									}
								}
								// Create Sprite using count
								else if (r.second->first_node("count") != 0)
								{

									std::string cnt = r.second->first_node("count")->value();
									// Exception for missing values
									if (cnt.empty())
									{
										std::cout << "ERROR: [RMParser::Load] Missing values for count of ";
										std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
										delete s;
										return false;
									}

									int count = std::stoi(cnt);

									if (!s->create(findSheet.first, count))
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Sprite for scene [" << scene << "] ";
										std::cout << "using pos count [" << count << "]" << std::endl;
										delete s;
										return false;
									}
								}
								else
								{
									std::cout << "ERROR: [RMParser::Load] Couldn't create Sprite [" << id << "] for scene [" << scene << "].";
									std::cout << " Invalid attributes in xml pack [" << pack_name << "]" << std::endl;
									delete s;
									return false;
								}

								s->setResourceID(id);
								s->setResourceFilePath(path);
								s->setResourceType(type);

								holder.listaSprites.push_back({ s, scene });

								// Found the resource, finish
								
								// Save last loaded ID
								currentID = id; 
								return true;
							}
						}

						// SpriteSheet not found
						std::cout << "ERROR: [RMParser::Load] Couldn't create Sprite [" << id << "] for scene [" << scene << "]. SpriteSheet [" << path << "] not found or not started." << std::endl;
						delete s;
						return false;
					}
					// case Animation:
					else if (type == "Animation")
					{
						Animation* a = new Animation();

						// Check if SpriteSheet is valid and alreadly initiated.
						for (std::pair<SpriteSheet *, std::string> findSheet : holder.listaSpriteSheet)
						{
							// SpriteSheet found
							if (findSheet.first->getResourceID() == path)
							{
								// Create Animation (using name duration) from MuSSE 
								if (r.second->first_node("name") != 0 && r.second->first_node("duration") != 0)
								{
									std::string name = r.second->first_node("name")->value();
									std::string dur = r.second->first_node("duration")->value();
									// Exception for missing values
									if (name.empty() || dur.empty())
									{
										std::cout << "ERROR: [RMParser::Load] Missing values for name or duration of ";
										std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
										delete a;
										return false;
									}
									int duration = std::stoi(dur);

									if (!a->create(findSheet.first, name, duration))
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "] ";
										std::cout << "using name [" << name << "] duration [" << duration << "]" << std::endl;
										delete a;
										return false;
									}
								}
								// creating Animation (using count frames duration)
								else if (r.second->first_node("count") != 0 && r.second->first_node("frames") != 0
									&& r.second->first_node("duration") != 0)
								{
									std::string cnt = r.second->first_node("count")->value();
									std::string fr = r.second->first_node("frames")->value();
									std::string dur = r.second->first_node("duration")->value();
									// Exception for missing values
									if (cnt.empty() || fr.empty() || dur.empty())
									{
										std::cout << "ERROR: [RMParser::Load] Missing values for count, frames or duration of ";
										std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
										delete a;
										return false;
									}

									int count = std::stoi(cnt);
									int frames = std::stoi(fr);
									int duration = std::stoi(dur);

									if (!a->create(findSheet.first, count, frames, duration))
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "] ";
										std::cout << "using count [" << count << "] frames [" << frames << "] duration [" << duration << "]" << std::endl;
										delete a;
										return false;
									}
								}
								// creating Animation (using posX posY frames duration)
								else if (r.second->first_node("sheet_pos_X") != 0 && r.second->first_node("sheet_pos_Y") != 0
									&& r.second->first_node("frames") != 0	&& r.second->first_node("duration") != 0)
								{
									std::string p_x = r.second->first_node("sheet_pos_X")->value();
									std::string p_y = r.second->first_node("sheet_pos_Y")->value();
									std::string fr = r.second->first_node("frames")->value();
									std::string dur = r.second->first_node("duration")->value();
									// Exception for missing values
									if (p_x.empty() || p_y.empty() || fr.empty() || dur.empty())
									{
										std::cout << "ERROR: [RMParser::Load] Missing values for sheet_pos_X, sheet_pos_Y, frames or duration of ";
										std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
										delete a;
										return false;
									}

									int sheet_pos_X = std::stoi(p_x);
									int sheet_pos_Y = std::stoi(p_y);
									int frames = std::stoi(fr);
									int duration = std::stoi(dur);

									if (!a->create(findSheet.first, sheet_pos_X, sheet_pos_Y, frames, duration))
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "] ";
										std::cout << "using pos X Y [" << sheet_pos_X << " " << sheet_pos_Y;
										std::cout << "] frames [" << frames << "] duration [" << duration << "]" << std::endl;
										delete a;
										return false;
									}
								}
								// creating Animation (using vector<pair<int, int>> pos vector<int> duration)
								else if (r.second->first_node("pos_list") != 0 && r.second->first_node("duration_list") != 0)
								{
									std::string pos_list = r.second->first_node("pos_list")->value();
									std::string duration_list = r.second->first_node("duration_list")->value();
									// Exception for missing values
									if (pos_list.empty() || duration_list.empty())
									{
										std::cout << "ERROR: [RMParser::Load] Missing values for pos_list or duration_list of ";
										std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
										delete a;
										return false;
									}

									std::vector<std::pair<int, int>> pos;
									std::vector<int> dur;

									// Parser for position list string
									int value1, value2;
									while (pos_list.find(',') != std::string::npos)
									{
										value1 = -1;
										value2 = -1;
										std::istringstream(pos_list) >> value1;
										pos_list.erase(0, pos_list.find(',') + 1);

										std::istringstream(pos_list) >> value2;
										// Deal with missing values before continuing
										if (value1 == -1 || value2 == -1)
										{
											std::cout << "ERROR: [RMParser::Load] Couldn't create Animation id [" << id << "] for scene [" << scene << "]. ";
											std::cout << "Missing values for position list. Check xml file." << std::endl;
											delete a;
											return false;
										}
										pos.push_back({ value1, value2 });
										//Erase all element including comma
										pos_list.erase(0, pos_list.find(',') + 1);
									}
									// Parser for duration list string
									int value;
									// Grab values before last comma ','
									while (duration_list.find(',') != std::string::npos)
									{
										value = -1;
										std::istringstream(duration_list) >> value;
										// Deal with missing values before continuing
										if (value == -1 )
										{
											std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "]. ";
											std::cout << "Missing values for duration list. Check xml file." << std::endl;
											delete a;
											return false;
										}
										dur.push_back(value);
										duration_list.erase(0, duration_list.find(',') + 1);
									}
									value = -1;
									// Grab last value
									std::istringstream(duration_list) >> value;
									if (value == -1)
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "]. ";
										std::cout << "Missing values for duration list. Check xml file." << std::endl;
										delete a;
										return false;
									}
									dur.push_back(value);

									if (!a->create(findSheet.first, pos, dur))
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "] ";
										std::cout << "from vector pos_list / duration_list." << std::endl;
										delete a;
										return false;
									}
								}
								// creating Animation (using vector<int> count vector<int> duration)
								else if (r.second->first_node("count_list") != 0 && r.second->first_node("duration_list") != 0)
								{
									std::string count_list = r.second->first_node("count_list")->value();
									std::string duration_list = r.second->first_node("duration_list")->value();
									// Exception for missing values
									if (count_list.empty() || duration_list.empty())
									{
										std::cout << "ERROR: [RMParser::Load] Missing values for count_list or duration_list of ";
										std::cout << "resource id [" << id << "] in scene [" << scene << "]" << std::endl;
										delete a;
										return false;
									}

									std::vector<int> count;
									std::vector<int> dur;

									// Parse for count_list string
									int valueC;
									// Grab values before last comma ','
									while (count_list.find(',') != std::string::npos)
									{
										valueC = -1;
										std::istringstream(count_list) >> valueC;
										// Deal with missing values before continuing
										if (valueC == -1)
										{
											std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "]. ";
											std::cout << "Missing values for count list. Check xml file." << std::endl;
											delete a;
											return false;
										}
										count.push_back(valueC);
										count_list.erase(0, count_list.find(',') + 1);
									}
									valueC = -1;
									// Grab last value
									std::istringstream(count_list) >> valueC;
									if (valueC == -1)
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "]. ";
										std::cout << "Missing values for count list. Check xml file." << std::endl;
										delete a;
										return false;
									}
									count.push_back(valueC);
									// Parser for duration list string
									int value;
									// Grab values before last comma ','
									while (duration_list.find(',') != std::string::npos)
									{
										value = -1;
										std::istringstream(duration_list) >> value;
										// Deal with missing values before continuing
										if (value == -1)
										{
											std::cout << "ERROR: [RMParser::Load] Couldn't create Animation for scene [" << scene << "]. ";
											std::cout << "Missing values for duration list. Check xml file." << std::endl;
											delete a;
											return false;
										}
										dur.push_back(value);
										duration_list.erase(0, duration_list.find(',') + 1);
									}
									value = -1;
									// Grab last value
									std::istringstream(duration_list) >> value;
									if (value == -1)
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "]. ";
										std::cout << "Missing values for duration list. Check xml file." << std::endl;
										delete a;
										return false;
									}
									dur.push_back(value);

									if (!a->create(findSheet.first, count, dur))
									{
										std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "] ";
										std::cout << "from vector count_list / duration_list." << std::endl;
										delete a;
										return false;
									}
								}
								else
								{
									std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "]. Invalid attributes in xml pack [" << pack_name << "]" << std::endl;
									delete a;
									return false;
								}

								a->setResourceID(id);
								a->setResourceFilePath(path);
								a->setResourceType(type);

								holder.listaAnimation.push_back({ a, scene });

								// Found the resource, finish
								
								// Save last loaded ID
								currentID = id; 
								return true;
							}
						}

						// SpriteSheet not found
						std::cout << "ERROR: [RMParser::Load] Couldn't create Animation [" << id << "] for scene [" << scene << "]. SpriteSheet [" << path << "] not found or not started." << std::endl;
						delete a;
						return false;

					}
					// case Sound:
					else if (type == "Sound"){
						std::cout << "ERROR: Type [" << type << "] not yet supported." << std::endl;
						return false;
					}
					// invalid
					else {
						std::cout << "ERROR: Invalid resource type [" << type << "] in pack [" << pack_name << "]" << std::endl;
						return false;
					}
				}
				// Didn't found resource, go to the next one
				skip++;
			}

			// Resource number (current) not found or out of bounds
			std::cout << "ERROR: [RMParser::LoadAll] Couldn't find resource [" << current << "] for scene " << scene << ". Out of bounds." << std::endl;
			return false;
		}
	}

	// Scene not found
	std::cout << "ERROR: [RMParser::LoadAll] Scene [" << scene << "] not found in XML." << std::endl;
	return false;
}

std::string ResourceManagerParser::getName() { return this->pack_name; }

std::string ResourceManagerParser::getCurrentID() 
{
	if (this->currentID == "") return "No resource loaded";
	else return this->currentID;
}
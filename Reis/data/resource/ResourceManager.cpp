#include "ResourceManager.h"

// Xml Parser with resources information
ResourceManagerParser parsed_xml;

// A Holder for the resources list: SpriteList, SpriteSheetList, AnimationList ...
ResourceHolder holder;

// Total and current resource loaded for each scene.
// Total ammount of resources per scene
TotalList totalAmmount;
// Index of current loaded resource per scene
IndexList currentIndex;

// Open xml file and make a list of resources for the scene.
bool ResourceManager::open(std::string xmlFile)
{
	// Load xml
	if (!parsed_xml.parseXmlFile(xmlFile.c_str())) {
		std::cout << "ERROR: [RM::open] Couldn't open file [" << xmlFile << "]" << std::endl;
		return false;
	}
	return true;
}

// Make 
bool ResourceManager::init(std::string scene)
{
	// Find resources for the scene
	if (!parsed_xml.getResourcesData(scene))
	{
		std::cout << "ERROR: [RM::init] Scene not found [" << scene << "]" << std::endl;
		return false;
	}

	// Success loading
		//std::cout << "DEBUG: Opening pack : " << parsed_xml.getName() << std::endl;
		//std::cout << "DEBUG: Initiating Scene : " << scene << std::endl;
	
	// Count resources for the scene
		int total_resources_in_scene = parsed_xml.getResourcesCount(scene);
		
		// Check if new scene
		TotalList::iterator i = totalAmmount.find(scene);

		if (i != totalAmmount.end()) 
		{ 
			/* Found */
			std::cout << "ERROR: [RM::init] Resource load for scene [" << scene << "] has alreadly been initiated." << std::endl;
			return false;
		}
		/* outra possibilidade:
			if ( !myMap.insert( std::make_pair( key, value ) ).second ) {
				//  Element already present...
			}
		*/
		// Scene is new, proceed.
		totalAmmount.insert({scene, total_resources_in_scene});
		//std::cout << "DEBUG: Total resources in scene " << scene << " [" << totalAmmount.find(scene)->second << "]\n";

		int current_resource_loaded = 0;
		currentIndex.insert({ scene, current_resource_loaded });
		//std::cout << "DEBUG: Current loaded    [" << currentIndex.find(scene)->second << "]\n";
		
		//std::cout << "DEBUG: Remaining resources [" << (totalAmmount.find(scene)->second - currentIndex.find(scene)->second) << "]\n";

		//std::cout << "DEBUG: Total resources in list    [" << parsed_xml.getResourcesCount() << "]\n";

	return true;
}

// Get total ammount of resources that are on the xml list for the current scene
int ResourceManager::getTotalResources(std::string scene)
{
	TotalList::iterator i = totalAmmount.find(scene);

	if (i != totalAmmount.end())
	{
		return i->second;
	}

	std::cout << "ERROR: [RM::TotalResources] Resources for scene [" << scene << "] don't exist." << std::endl;
	return 0;
}

// Get how many resources have been loaded (current) for the scene
int ResourceManager::getResourcesLoaded(std::string scene)
{
	IndexList::iterator c = currentIndex.find(scene);

	if (c != currentIndex.end())
	{
		return c->second;
	}
	
	std::cout << "ERROR: [RM::ResourcesLoaded] Resources for scene [" << scene << "] don't exist." << std::endl;
	return 0;
}

// Get how many resources still need to be loaded for the scene
int ResourceManager::getRemainingResources(std::string scene)
{
	return getTotalResources(scene) - getResourcesLoaded(scene);
}

// Get loading % for the current scene based on total resources and remaning resources
float ResourceManager::getResourcesLoadedProgress(std::string scene)
{
	int total = getTotalResources(scene);
	int loaded = getResourcesLoaded(scene);

	if (total > 0) return ((float)loaded / (float)total) * 100;
	
	std::cout << "ERROR: [RM::ResourcesLoadedProgress] Resources for scene [" << scene << "] don't exist." << std::endl;
	return 0;
}

bool ResourceManager::loadNext(std::string scene)
{
	// If there'r still resources to load
	if (getResourcesLoadedProgress(scene) < 100)
	{
		// Find the current resource we need to load
		IndexList::iterator c = currentIndex.find(scene);
		int current = c->second;

		if (parsed_xml.loadNext(holder, scene, current))
		{
			// Loaded successfully, update index (current resource) for the scene
			c->second++;
			return true;
		}
	}
	
	std::cout << "ERROR: [RM::LoadNext] Couldn't load resource : end of stack or xml error." << std::endl;
	return false;
}

bool ResourceManager::loadAll(std::string scene)
{
	int total = getTotalResources(scene);
	int current = getResourcesLoaded(scene);

	if (total > 0) 
	{
		// Run from current (last loaded) resource to last
		for (current; current < total; current++)
		{
			// Load current resource
			if (!loadNext(scene))
			{
				std::cout << "ERROR: [RM::LoadAll] Load next resource for scene [" << scene << "] failed." << std::endl;
				return false;
			}
		}

		return true;
	}

	std::cout << "ERROR: [RM::LoadAll] Resources for scene [" << scene << "] don't exist." << std::endl;
	return false;
}

Sprite * ResourceManager::getSprite(std::string resourceID)
{
	// Start iterator on SpriteList
	for (std::pair<Sprite *, std::string> r : holder.listaSprites)
	{
		// Find Sprite with target ID
		if (r.first->getResourceID() == resourceID)
		{
			// Return Sprite to user
			return r.first;
		}
	}

	// Resource not found exception
	std::cout << "ERROR: [RM::getSprite] Couldn't find resource [" << resourceID << "]. Not loaded or invalid ID.\n";
	throw std::invalid_argument("ERROR: [RM::getSprite] Couldn't find resource. Not loaded or invalid ID.\n");
}

SpriteSheet * ResourceManager::getSpriteSheet(std::string resourceID)
{
	// Start iterator for SpriteSheetList
	for (std::pair<SpriteSheet *, std::string> r : holder.listaSpriteSheet)
	{
		// Find SpriteSheet with target ID
		if (r.first->getResourceID() == resourceID)
		{
			// Return SpriteSheet to user
			return r.first;
		}
	}

	// Resource not found exception
	std::cout << "ERROR: [RM::getSpriteSheet] Couldn't find resource [" << resourceID << "]. Not loaded or invalid ID.\n";
	throw std::invalid_argument(" ERROR: [RM::getSpriteSheet] Couldn't find resource. Not loaded or invalid ID.\n");
}

Animation * ResourceManager::getAnimation(std::string resourceID)
{
	// Start iterator for AnimationList
	for (std::pair<Animation *, std::string> r : holder.listaAnimation)
	{
		// Find Animation with target ID
		if (r.first->getResourceID() == resourceID)
		{
			// Return Animation to user
			return r.first;
		}
	}

	// Resource not found exception
	std::cout << "ERROR: [RM::getAnimation] Couldn't find resource [" << resourceID << "]. Not loaded or invalid ID.\n";
	throw std::invalid_argument(" ERROR: [RM::getAnimation] Couldn't find resource. Not loaded or invalid ID.\n");
}

void ResourceManager::end(std::string scene)
{
	/*
		-----------------
		Clear Sprite List
		-----------------
	*/
	// Iterator for SpriteList
	auto sprites = holder.listaSprites.begin();
	while (sprites != holder.listaSprites.end())
	{
		// Check if resource belongs to scene
		if (sprites->second == scene) {
			// Remove
			//std::cout << "DEBUG: Freeing resource : " << sprites->first->getResourceID() << std::endl;
			if (sprites->first != NULL) {
				sprites->first->free();
				delete sprites->first;
				sprites->first = NULL;
			}
			else {
				// I think this will never trigger 'cause listaSprites shall not be NULL by default (otherwise loop won't start).
				// But anyway, this is programming. Care should never be too much.
				std::cout << "ERROR: [RM::end] NullPointerException while freeing Sprite resource for scene [" << scene << "]" << std::endl;
			}

			sprites = holder.listaSprites.erase(sprites);
			// Vector (C++11) self adjusts positions
			//std::cout << "DEBUG: Loaded sprites size [" << holder.listaSprites.size() << "]\n";
		}
		// Skip resources that don't belong to the scene
		else ++sprites;
	}

	/*
	----------------------
	Clean Animation List
	----------------------
	*/
	// Iterator for AnimationList
	auto anims = holder.listaAnimation.begin();
	while (anims != holder.listaAnimation.end())
	{
		// Check if resource belongs to scene
		if (anims->second == scene) {
			// Remove
			//std::cout << "DEBUG: Freeing resource : " << anims->first->getResourceID() << std::endl;

			if (anims->first != NULL) {
				delete anims->first;
				anims->first = NULL;
			}
			else {
				std::cout << "ERROR: [RM::end] NullPointerException while freeing Animation resource for scene [" << scene << "]" << std::endl;
			}
			
			anims = holder.listaAnimation.erase(anims);
			// Vector (C++11) self adjust positions
			//std::cout << "DEBUG: Loaded animations size [" << holder.listaAnimation.size() << "]\n";
		}
		// Skip resources that don't belong to the scene
		else ++anims;
	}

	/*
		----------------------
		Clean SpriteSheet List
		----------------------
	*/
	// Iterator for SpriteSheetList
	auto sheets = holder.listaSpriteSheet.begin();
	while (sheets != holder.listaSpriteSheet.end())
	{
		// Check if resource belongs to scene
		if (sheets->second == scene) {
			// Remove
			//std::cout << "DEBUG: Freeing resource : " << sheets->first->getResourceID() << std::endl;
			if (sheets->first != NULL) {
				sheets->first->free();
				delete sheets->first;
				sheets->first = NULL;
			}
			else {
				std::cout << "ERROR: [RM::end] NullPointerException while freeing SpriteSheet resource for scene [" << scene << "]" << std::endl;
			}

			sheets = holder.listaSpriteSheet.erase(sheets);
			// Vector (C++11) self adjust positions
			//std::cout << "DEBUG: Loaded sheets size [" << holder.listaSpriteSheet.size() << "]\n";
		}
		// Skip resources that don't belong to the scene
		else ++sheets;
	}

	// Clean Total List for scene
	totalAmmount.erase(scene);
	// Clean Index List for scene
	currentIndex.erase(scene);
}

std::string ResourceManager::getCurrentID()
{
	return parsed_xml.getCurrentID();
}
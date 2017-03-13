#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../xml/ResourceManagerParser.h"
#include <map>

// Total ammount of resources per scene
using TotalList = std::map<std::string, int>;
// Index of current loaded resource per scene
using IndexList = std::map<std::string, int>;

/**
 * @brief      A Resource Manager to handle loading and unloading resources (Sprites, Animations, SFX, Music etc).
 * 
 * @author     marcelomesmo
 */
namespace ResourceManager
{
	/**
	 * @brief      Open xml file. Need to do only once per game.
	 *
	 * @param[in]  xmlFile  The xml file.
	 *
	 * @return     True if loaded successfully.
	 */
	bool open(std::string xmlFile);

	/**
	 * @brief      Make a list of resources for the scene. Need to do this for
	 *             every scene. Init all resource lists and queue scene for loading.
	 *
	 * @param[in]  scene  The scene you want to init.
	 *
	 * @return     True if scene init is ok.
	 */
	bool init(std::string scene);

	/**
	 * @brief      Load all resources on the list.
	 *
	 * @param[in]  scene  The scene you want to load.
	 *
	 * @return     True if resource lists are loaded successfully.
	 */
	bool loadAll(std::string scene);
	/**
	 * @brief      Load next resource on the list (until it's empty).
	 *
	 * @param[in]  scene  The scene you want to load.
	 *
	 * @return     True if resource is loaded successfully.
	 */
	bool loadNext(std::string scene);

	/**
	 * @brief      Gets the Sprite.
	 *
	 * @param[in]  resourceID  Sprite ID.
	 *
	 * @return     The Sprite.
	 */
	Sprite * getSprite(std::string resourceID);
	/**
	 * @brief      Gets the Sprite Sheet.
	 *
	 * @param[in]  resourceID  Sprite Sheet ID.
	 *
	 * @return     The Sprite Sheet.
	 */
	SpriteSheet * getSpriteSheet(std::string resourceID);
	/**
	 * @brief      Gets the Animation.
	 *
	 * @param[in]  resourceID  Animation ID.
	 *
	 * @return     The Animation.
	 */
	Animation * getAnimation(std::string resourceID);

	/**
	 * @brief      Clear the list of resources for the scene. Free all objects used.
	 *
	 * @param[in]  scene  The scene you want to unload.
	 */
	void end(std::string scene);

	/**
	 * @brief      Gets the total ammount of resources for the current scene.
	 *
	 * @param[in]  scene  The scene.
	 *
	 * @return     Total resources.
	 */
	int getTotalResources(std::string scene);
	/**
	 * @brief      Gets how many resources still need to be loaded for the current scene.
	 *
	 * @param[in]  scene  The scene.
	 *
	 * @return     Remaining resources to be loaded.
	 */
	int getRemainingResources(std::string scene);
	/**
	 * @brief      Gets the ammount of resources loaded.
	 *
	 * @param[in]  scene  The scene.
	 *
	 * @return     Total resources loaded.
	 */
	int getResourcesLoaded(std::string scene);
	/**
	 * @brief      Get loading progress (%) for the scene. Based on total and remaning resources.
	 *
	 * @param[in]  scene  The scene.
	 *
	 * @return     Resource load progress percentage.
	 */
	float getResourcesLoadedProgress(std::string scene);

	/**
	 * @brief      Gets the last loaded esource ID. Useful for debugging.
	 *
	 * @return     Last loaded resource ID.
	 */
	std::string getCurrentID();

};

#endif
#ifndef RESOURCEPARSER_H
#define RESOURCEPARSER_H

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
using namespace rapidxml;

#include <sstream>

#include "../resource/ResourceHolder.h"

/**
* @brief      XMLParser in C++ to read Resource files.
*
* @author     marcelomesmo
*/
class ResourceManagerParser
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
	 * @brief      Get all the meta-data for resources in the scene and place
	 *             them in a vector of <scene, xml_nodes>.
	 *
	 * @param[in]  scene  The scene.
	 *
	 * @return     True if loaded successfully.
	 */
	bool getResourcesData(std::string scene);

	/**
	 * @brief      Load next resource.
	 *
	 *             Won't load multiple ocurrancies of a scene in the xml file:
	 *             user shall pack all scene resources in the same branch.
	 *
	 * @param      holder   Container with all resource lists.
	 * @param[in]  scene    The scene.
	 * @param[in]  current  Current resource index.
	 *
	 * @return     True if loaded successfully.
	 */
	bool loadNext(ResourceHolder & holder, std::string scene, int current);

	/**
	 * @brief      Gets total ammount of resources for the scene.
	 *
	 * @param[in]  scene  The scene.
	 *
	 * @return     Total resources.
	 */
	int getResourcesCount(std::string scene);
	/**
	 * @brief      Gets total ammount of resources in xml file, among all init. scenes.
	 *
	 * @return     Total resources for all init scenes.
	 */
	int getResourcesCount();

	/**
	 * @brief      Gets the asset pack name.
	 *
	 * @return     Pack name.
	 */
	std::string getName();

	/**
	 * @brief      Gets the last loaded resource ID.
	 *
	 * @return     Last loaded resource id.
	 */
	std::string getCurrentID();

private:
	std::stringstream buffer;
	std::string content;
	// XML document to be parsed
	xml_document<> doc;
	// A doc (xml_document) has an assets for the game. Assets have a pack_name. 
	// Also, assets have scenes. Each scene has a resource list.
	xml_node<> *assets;
		std::string pack_name;
	xml_node<> *scenes;	
	// Inside each scene we have a list of resources (xml_node<>)
	std::vector< std::pair<std::string, xml_node<>*> > resources;

	// Last loaded resource id
	std::string currentID;

};

#endif
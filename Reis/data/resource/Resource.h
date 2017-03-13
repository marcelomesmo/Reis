#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

/**
 * @brief      Base class for Resources.
 * @details    Every asset in the game is a Resource: Sprites, SpriteSheet, SFX,
 *             Music etc. This is a base abstract class for creating specific
 *             types of resources, maintaining assets ID, type and file path.
 * @author     marcelomesmo
 */
class Resource
{
public:
	virtual ~Resource() = 0;

	/**
	 * @brief      Gets the resource id.
	 *
	 * @return     The resource id.
	 */
	std::string getResourceID();
	/**
	 * @brief      Sets the resource id.
	 *
	 * @param[in]  id    The identifier
	 */
	void setResourceID(std::string id);

	/**
	 * @brief      Gets the resource file path.
	 *
	 *             Sprites and Animations will return SpriteSheet's name (if
	 *             applicable).
	 *
	 * @return     The resource file path.
	 */
	std::string getResourceFilePath();
	/**
	 * @brief      Sets the resource file path.
	 *
	 * @param[in]  filepath  The filepath
	 */
	void setResourceFilePath(std::string filepath);

	/**
	 * @brief      Gets the resource type.
	 *
	 *             Current support: ISprite, Sprite, SpriteSheet, Animation,
	 *
	 * @return     The resource type.
	 */
	std::string getResourceType();
	/**
	 * @brief      Sets the resource type.
	 *
	 * @param[in]  type  The type
	 */
	void setResourceType(std::string type);

private:
	// Resource id.
	std::string ID;
	// Resource file path or sheet name.
	std::string path;
	// Resource type.
	std::string type;
};

#endif
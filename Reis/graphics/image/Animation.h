#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <utility>
#include "../../data/timer/Clock.h"
#include "Sprite.h"

/**
* @brief      Create a new Animation.
*
* @author     marcelomesmo
*/
class Animation : public Resource
{
public:
	/*Animation(vector<Sprite*> spriteList);
	Animation(SpriteSheet* sheet, int count, int frames, int duration);
	Animation(SpriteSheet* sheet, int sheetPosX, int sheetPosY, int frames, int duration);*/
	Animation();

	/**
	* @brief      Create a new Animation object.
	*
	*             Using Sprite position and Sprite quantity.
	*
	* @param      sheet     SpriteSheet used to get Sprites for the Animation.
	* @param[in]  count     Ordered count position of the initial Sprite in the
	*                       SpriteSheet.
	* @param[in]  frames    Number of aditional Sprites to add after the
	*                       first one.
	* @param[in]  duration  Duration of each Sprite in the Animation.
	*
	* @return     True if loaded successfully.
	*/
	bool create(SpriteSheet* sheet, int count, int frames, int duration);
	/**
	* @brief      Create a new Animation object.
	*
	*             Using Sprite position and Sprite quantity.
	*
	* @param      sheet      SpriteSheet used to get Sprites for the Animation.
	* @param[in]  sheetPosX  The X position of the cell on the SpriteSheet.
	* @param[in]  sheetPosY  The Y position of the cell on the SpriteSheet.
	* @param[in]  frames     Number of aditional Sprites to add after the
	*                        first one.
	* @param[in]  duration   Duration of each Sprite in the Animation.
	*
	* @return     True if loaded successfully.
	*/
	bool create(SpriteSheet* sheet, int sheetPosX, int sheetPosY, int frames, int duration);
	/**
	* @brief      Create a new Animation object.
	*
	*             Using a vector of Sprite positions and individual duration
	*             for each Sprite.
	*
	* @param      sheet      SpriteSheet used to get Sprites for the Animation.
	* @param[in]  sheetPos   Vector of Sprite positions in the sheet.
	* @param[in]  duration   Vector of time duration for each Sprite in the Animation.
	*
	* @return     True if loaded successfully.
	*/
	bool create(SpriteSheet* sheet, std::vector<std::pair<int, int>> sheetPos, std::vector<int> duration);
	/**
	* @brief      Create a new Animation object.
	*
	*             Using a vector of Sprite positions and individual duration
	*             for each Sprite.
	*
	* @param      sheet     SpriteSheet used to get Sprites for the Animation.
	* @param[in]  count     Vector of Sprite ordered count positions in the
	*                       sheet.
	* @param[in]  duration  Vector of time duration for each Sprite in the
	*                       Animation.
	*
	* @return     True if loaded successfully.
	*/
	bool create(SpriteSheet* sheet, std::vector<int> count, std::vector<int> duration);
	/**
	 * @brief      Create a new Animation object.
	 *
	 *             Using a vector of Sprite positions and individual duration
	 *             for each Sprite.
	 *
	 * @param      sheet     SpriteSheet used to get Sprites for the Animation.
	 * @param[in]  name      Animation name in the XML file.
	 * @param[in]  duration  Duration of each Sprite in the Animation.
	 *
	 * @return     True if loaded successfully.
	 */
	bool create(SpriteSheet* sheet, std::string name, int duration);

	~Animation();
	// No need, since every image in the animation is referenced by a sheet. So, will also
	// be deallocated when the sheet is.
	// No need to free the Sprite list (sprites), when Animation dies they die.
	// void free();

	/**
	 * @brief      Add a new Sprite to the Animation.
	 *
	 * @param      sheet     SpriteSheet used to get Sprites for the Animation.
	 * @param[in]  count     Sprite position in the Sprite Sheet.
	 * @param[in]  duration  Duration of this Sprite in the Animation.
	 *
	 * @return     True if loaded successfully.
	 */
	bool addFrame(SpriteSheet* sheet, int count, int duration);
	/**
	 * @brief      Add a new Sprite to the Animation.
	 *
	 * @param      sheet      SpriteSheet used to get Sprites for the Animation.
	 * @param[in]  sheetPosX  The X position of the cell on the SpriteSheet.
	 * @param[in]  sheetPosY  The Y position of the cell on the SpriteSheet.
	 * @param[in]  duration   Duration of this Sprite in the Animation.
	 *
	 * @return     True if loaded successfully.
	 */
	bool addFrame(SpriteSheet* sheet, int sheetPosX, int sheetPosY, int duration);
	/**
	 * @brief      Add a new Sprite to the Animation.
	 *
	 * @param      sheet     SpriteSheet used to get Sprites for the Animation.
	 * @param      clip      Sprite clip from XML file.
	 * @param[in]  duration  Duration of this Sprite in the Animation.
	 *
	 * @return     True if loaded successfully.
	 */
	bool addFrame(SpriteSheet* sheet, SDL_Rect* clip, int duration);

	/**
	* @brief      Render Animation on screen.
	*
	* @param[in]  x        Start position X.
	* @param[in]  y        Start position Y.
	* @param[in]  flipped  Flip::HORIZONTAL to draw image flipped on x-axis or
	*                      Flip::VERTICAL to draw image flipped on y-axis.
	*                      Flip::NONE by default.
	*/
	void draw(int x, int y, Flip flipped = Flip::NONE);

	/**
	* @brief      Force Animation to pass on to next frame.
	*
	*             No need to call this unless you want to force a sprite
	*             change.
	*/
	void nextFrame();

	/**
	* @brief      Starts or Unpause the Animation.
	*/
	void start();
	/**
	* @brief      Stop (pause) the Animation in current frame.
	*/
	void pause();
	/**
	* @brief      Finish the Animation. Won't be draw anymore.
	*/
	void end();
	/**
	* @brief      Restart the Animation. Stop and Start from the beginning.
	*/
	void restart();

	/**
	* @brief      Tells if the Animation has already started.
	*
	* @return     True if started.
	*/
	bool isRunning();
	/**
	* @brief      Tells if the Animation has finished.
	*
	*             To kill the Animation call .end().
	*
	* @return     True if first loop in the Animation is complete.
	*/
	bool hasFinished();

	/**
	* @brief      Set the Animation to auto-loop.
	*
	*             True by default. If set to False will Pause at the last
	*             frame.
	*
	* @param[in]  repeat  Set Animation to auto-loop.
	*/
	void setAutoRepeat(bool repeat);

	/**
	 * @brief      Set the duration of a individual Sprite frame in the
	 *             Animation.
	 *
	 * @param[in]  count         Sprite position in the Animation.
	 * @param[in]  new_duration  New duration for the Sprite frame.
	 */
	void setDuration(int count, int new_duration);

private:

	std::vector<Sprite> sprites;

	// Tells if we need to repeat the animation when it finishes running.
	bool autoRepeat;

	// Tells if the animation is running.
	bool running;
	bool ended;

	// Clock that controls the animation flow.
	Clock timer;
	std::vector<unsigned int> duration;
	// Will cap the duration of each frame in animation.

	// Current animation frame
	int frame;
	// Starting frame position on sheet
	int start_frame;
	// Total frames to count
	int total_frames;
};

#endif
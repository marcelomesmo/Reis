#include "Animation.h"

Animation::Animation()
{
	timer.start();

	this->running = true;
	this->ended = false;

	this->frame = 0;					// Start counting frames
	this->start_frame = 0;				// Gets the starting frame position
	this->total_frames = 0;				// How many frames will count

	this->autoRepeat = true;
}

Animation::~Animation()
{

}

bool Animation::create(SpriteSheet* sheet, int count, int frames, int duration)
{
	for (int i = count; i < count + frames; i++) addFrame(sheet, i, duration);
	return true;
}
bool Animation::create(SpriteSheet* sheet, int sheetPosX, int sheetPosY, int frames, int duration)
{
	int count = sheet->getSpriteCountByPos(sheetPosX, sheetPosY);
	for (int i = count; i < count + frames; i++) addFrame(sheet, i, duration);
	return true;
}
bool Animation::create(SpriteSheet* sheet, std::vector<std::pair<int, int>> sheetPos, std::vector<int> duration)
{
	// Duration vector has same size than SheetPos vector
	if (sheetPos.size() != duration.size())
	{
		printf("ERROR: [Animation::create] sheetPos and duration have invalid sizes (duration must be same size of sheetPos)\n");
		return false;
	}
	std::vector<int> count;
	// Get every position we must add to the Animation as a count
	for (unsigned int i = 0; i < sheetPos.size(); i++) count.push_back(sheet->getSpriteCountByPos(sheetPos.at(i).first, sheetPos.at(i).second));

	// For every position (count and duration must have same size) add to Animation
	for (unsigned int i = 0; i < count.size(); i++) addFrame(sheet, count.at(i), duration.at(i));
	return true;
}
bool Animation::create(SpriteSheet* sheet, std::vector<int> count, std::vector<int> duration)
{
	// Duration vector must have same size than Count vector
	if (count.size() != duration.size())
	{
		printf("ERROR: [Animation::create] count and duration have invalid sizes (duration must be the same size of count)\n");
		return false;
	}
	// For every position (count and duration must have same size) add to Animation
	for (unsigned int i = 0; i < count.size(); i++) addFrame(sheet, count.at(i), duration.at(i));
	return true;
}
bool Animation::create(SpriteSheet* sheet, std::string name, int duration)
{
	// Invalid Clip or Animation dont exist for that name
	if (!sheet->hasAnimation(name)) return false;

	std::vector<Sprite_Xml> sprites = sheet->getAnimation(name);

	if (sprites.size() <= 0) {
		std::cout << "ERROR: [Animation::create] Couldn't create Animation using Xml. Sprites not found.\n";
		return false;
	}

	for( unsigned int i = 0; i < sprites.size(); i++) addFrame(sheet, sprites.at(i), duration);

	//Sucess create anim
	return true;
}

bool Animation::addFrame(SpriteSheet* sheet, int count, int duration)
{
	Sprite novo;
	if (!novo.create(sheet, count)) return false;

	this->sprites.push_back(novo);
	this->total_frames++;
	this->duration.push_back(duration);

	return true;
}
bool Animation::addFrame(SpriteSheet* sheet, int sheetPosX, int sheetPosY, int duration)
{
	int count =	sheet->getSpriteCountByPos(sheetPosX, sheetPosY);
	return addFrame(sheet, count, duration);
}
bool Animation::addFrame(SpriteSheet* sheet, SDL_Rect* clip, int duration)
{
	Sprite novo;
	if (!novo.create(sheet, clip)) return false;

	this->sprites.push_back(novo);
	this->total_frames++;
	this->duration.push_back(duration);

	return true;
}
bool Animation::addFrame(SpriteSheet* sheet, Sprite_Xml s, int duration)
{
	Sprite novo;
	if (!novo.create(sheet, s.clip)) return false;

	novo.setAnchorX(s.ancX);
	novo.setAnchorY(s.ancY);
	
	novo.setResourceID(s.name);
	novo.setResourceFilePath(s.name);
	novo.setResourceType("Sprite");

	this->sprites.push_back(novo);
	this->total_frames++;
	this->duration.push_back(duration);

	return true;
}
void Animation::draw(int x, int y, Flip flipped)
{
	if (running && total_frames > 0)
	{
		sprites.at(start_frame + frame).draw(x, y, flipped);
		// Check framerate? do need?
		if (timer.getTicks() > duration.at(start_frame + frame)) this->nextFrame();
	}
}

void Animation::nextFrame()
{
	frame++;				// Swap to next frame
	timer.start();			// Restart timer for next frame
	// If we get to the end
	if (frame > total_frames - 1)
	{
		// Loop through frames in case repeat is on
		if (autoRepeat) frame = 0;
		// Stop at last frame in case repeat is off
		else frame = total_frames - 1;
		ended = true;		// In case we need to check if animation completed first loop
	}
}

void Animation::setAutoRepeat(bool repeat) { this->autoRepeat = repeat; }

void Animation::setDuration(int count, int new_duration)
{ 
	if(count < 0 || (unsigned int) count > this->duration.size() - 1){
		printf("ERROR: [Animation::setDuration] Can't change duration: invalid frame in Animation.\n");
		return;
	}
	this->duration.at(count) = new_duration; 
}

bool Animation::isRunning() { return this->running; }
bool Animation::hasFinished() { return this->ended; }
void Animation::start() {
	// Paused Only
	if (running)
	{
		timer.unpause();
		return;
	}
	// Start from beginning
	this->running = true;
	this->ended = false;
	this->frame = 0;
	timer.start();
}
void Animation::pause() {
	if (!running) return;
	timer.pause();
}
void Animation::end() {
	if (!running) return;
	this->running = false;
	this->ended = true;
	this->frame = 0;
	timer.stop();
}
void Animation::restart() {
	this->end();
	this->start();
}
#ifndef			__HPP__ANIMATEDSPRITE__
#define			__HPP__ANIMATEDSPRITE__

#include "Sprite.hpp"
#include "Utility.hpp"
#include <string>
#include <vector>
#include <SDL.h>

// code taken from the textbook
struct AnimFrameData {
	// The index of the first frame of an animation
	int startFrame;
	// The total number of frames for a particulare animation
	int numFrames;
};

struct AnimData {
	// Array of images for all animations for a sprite
	std::vector<SDL_Rect*> images;
	// Frame data array for each of the animations for the sprite
	std::vector<AnimFrameData*> frameInfo;
};

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(std::string spriteSheetPath, int sortingLayer, AnimData* inputAnimData, int startingAnimNum);
	~AnimatedSprite();

	void draw();

protected:
	AnimData* animationData;
	int animNum;
	int frameNum;
	float frameTime;
	float animFPS;
	SDL_Rect* currentImage;

	void ChangeAnimation(int animationNum);
	void UpdateAnimation(float delta);
	
};

#endif
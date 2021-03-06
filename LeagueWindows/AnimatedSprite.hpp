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

// Subclass of sprite that provides animation functionality. Most functionality is 
// adapted from the book "Game Programming Algorithms and Techniques" by 
// Sanjay Madhav
class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(std::string spriteSheetPath, int sortingLayer, AnimData* inputAnimData, int startingAnimNum);
	AnimatedSprite(std::string spriteSheetPath, int sortingLayer, int startingAnimNum);
	~AnimatedSprite();
	void draw();

protected:
	// all data for all sprites and animations for this GameObject
	AnimData* animationData;
	// The particular animation that is active
	int animNum;
	// The frame number of the specific animation that is active
	int frameNum;
	// The amount of time the current frame has been displayed
	float frameTime;
	// The FPS the animation is running at 
	float animFPS;

	// The coordinates on the spritesheet of the current image being displayed
	SDL_Rect* currentImage;

	// The factor by which we scale the current image as we draw it
	double currentImageScale;

	//Used to set up animation data after object has been instantiated
	void setAnimData(AnimData *animData, int startingAnimNum);

	// changes which animation is active (think changing from walk to sword swing)
	void ChangeAnimation(int animationNum);

	// updates the current animation (think from one part of walk cycle to the next)
	void UpdateAnimation(float delta);
	
};

#endif
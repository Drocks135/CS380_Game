#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "Sprite.hpp"
#include "Utility.hpp"
#include <string>
#include <SDL.h>

AnimatedSprite::AnimatedSprite(std::string spriteSheetPath, int sortingLayer, AnimData* inputAnimData, int startingAnimNum) : Sprite(spriteSheetPath, sortingLayer){
	// get animation info
	animationData = inputAnimData;
	animNum = startingAnimNum;
	frameNum = 0;
	frameTime = 0.0f;
	animFPS = 12.0f;

	// set the current animation
	int imageNum = inputAnimData->frameInfo.at(startingAnimNum)->startFrame;
	currentImage = inputAnimData->images.at(imageNum);
	currentImageScale = 1;
}

AnimatedSprite::AnimatedSprite(std::string spriteSheetPath, int sortingLayer, int startingAnimNum) : Sprite(spriteSheetPath, sortingLayer) {
	// get animation info
	animNum = startingAnimNum;
	frameNum = 0;
	frameTime = 0.0f;
	animFPS = 12.0f;

	// set the current animation
	
	currentImageScale = 1;
}

void AnimatedSprite::setAnimData(AnimData* animData, int startingAnimNum) {
	animationData = animData;
	int imageNum = animData->frameInfo.at(startingAnimNum)->startFrame;
	currentImage = animData->images.at(imageNum);
}

void AnimatedSprite::ChangeAnimation(int animationNum) {
	// set the new animation and make it start at the 0th frame
	animNum = animationNum;

	frameNum = 0;
	frameTime = 0.0f;

	int imageNum = animationData->frameInfo.at(animNum)->startFrame;
	currentImage = animationData->images.at(imageNum);
	
}

void AnimatedSprite::UpdateAnimation(float delta) {
	frameTime += delta;

	// if enough time has passed to advance the animation
	if (frameTime > (1 / animFPS)) {
		// find the frame number of the animation we should play based on animFPS
		frameNum += frameTime * animFPS;
		
		// if the frame is outside the bounds of the animation, loop back to animation beginning
		if (frameNum >= animationData->frameInfo.at(animNum)->numFrames) {
			frameNum = frameNum % animationData->frameInfo.at(animNum)->numFrames;
		}

		//update the active image
		int imageNum = animationData->frameInfo.at(animNum)->startFrame + frameNum;
		currentImage = animationData->images.at(imageNum);

		// update the current frame time
		frameTime = fmod(frameTime, 1 / animFPS);
	}
}

void AnimatedSprite::draw() {
	SDL_Rect dst;
	dst.x = position.getX();
	dst.y = position.getY();
	dst.w = currentImage->w * currentImageScale;
	dst.h = currentImage->h * currentImageScale;
	// draw only the part of the spritesheet corresponding to our current animation 
	SDL_RenderCopy(Engine::getRenderer(), texture, currentImage, &dst);
}

AnimatedSprite::~AnimatedSprite() {
	// TODO destruct the SDL_Rect?
}
#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "Sprite.hpp"
#include "Utility.hpp"
#include <string>
#include <SDL.h>

AnimatedSprite::AnimatedSprite(std::string spriteSheetPath, int sortingLayer, AnimData* inputAnimData, int startingAnimNum) : Sprite(spriteSheetPath, sortingLayer){
	animationData = inputAnimData;
	animNum = startingAnimNum;
	frameNum = 0;
	frameTime = 0.0f;
	animFPS = 24.0f;

	int imageNum = inputAnimData->frameInfo.at(startingAnimNum)->startFrame;
	currentImage = inputAnimData->images.at(imageNum);

	// todo: change starting rect
	// currentImage = rect;
}

void AnimatedSprite::ChangeAnimation(int animationNum) {
	animNum = animationNum;

	frameNum = 0;
	frameTime = 0.0f;

	int imageNum = animationData->frameInfo.at(animNum)->startFrame;
	currentImage = animationData->images.at(imageNum);
	
}

void AnimatedSprite::UpdateAnimation(float delta) {
	frameTime += delta;

	// if enough time has passed to advance the frame
	if (frameTime > (1 / animFPS)) {
		frameNum += frameTime * animFPS;
		
		if (frameNum >= animationData->frameInfo.at(animNum)->numFrames) {
			frameNum = frameNum % animationData->frameInfo.at(animNum)->numFrames;
		}

		//update the active image
		int imageNum = animationData->frameInfo.at(animNum)->startFrame + frameNum;
		currentImage = animationData->images.at(imageNum);

		frameTime = fmod(frameTime, 1 / animFPS);
	}
}

void AnimatedSprite::draw() {
	SDL_Rect* dst = new SDL_Rect();
	dst->x = position.getX();
	dst->y = position.getY();
	dst->w = currentImage->w * 3;
	dst->h = currentImage->h * 3;
	//todo: render from source rect rather than null
	SDL_RenderCopy(Engine::getRenderer(), texture, currentImage, dst);
}

AnimatedSprite::~AnimatedSprite() {
	// destruct the SDL_Rect
}
#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "LifeBar.hpp"
#include <SDL.h>

LifeBar::LifeBar() : AnimatedSprite("../assets/LifeBar.png", 1, 0) {
	position.setX(0);
	position.setY(734);

	AnimFrameData down;
	down.startFrame = 0;
	down.numFrames = 0;


	//start x, start y, width, height
	SDL_Rect* downRect = new SDL_Rect{ 8, 8, 202, 34 };
	SDL_Rect* upRect = new SDL_Rect{ 8, 53, 202, 34 };
	SDL_Rect* leftRect = new SDL_Rect{ 8, 134, 202, 34 };
	SDL_Rect* rightRect = new SDL_Rect{ 8, 171, 202, 34 };
	SDL_Rect* lastRect = new SDL_Rect{ 8, 209, 202, 34 };

	AnimData HealthAnimationData;
	HealthAnimationData.frameInfo.push_back(down);
	HealthAnimationData.images.push_back(downRect);
	HealthAnimationData.images.push_back(upRect);
	HealthAnimationData.images.push_back(leftRect);
	HealthAnimationData.images.push_back(rightRect);
	HealthAnimationData.images.push_back(lastRect);

	AnimatedSprite::setAnimData(&PlayerAnimationData);
}


LifeBar::~LifeBar() {
	SDL_Log("Destrucing Player");
}

void LifeBar::setLife() {
	ChangeAnimation(health);
}

void LifeBar::update(double delta) {
	LifeBar::setLife();
}
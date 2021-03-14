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
	SDL_Rect* fiveHealth = new SDL_Rect{ 8, 8, 202, 34 };
	SDL_Rect* fourHealth = new SDL_Rect{ 8, 53, 202, 34 };
	SDL_Rect* threeHealth = new SDL_Rect{ 8, 96, 202, 34 };
	SDL_Rect* twoHealth = new SDL_Rect{ 8, 134, 202, 34 };
	SDL_Rect* oneHealth = new SDL_Rect{ 8, 171, 202, 34 };
	SDL_Rect* zeroHealth = new SDL_Rect{ 8, 209, 202, 34 };
	

	AnimData HealthAnimationData;
	HealthAnimationData.images.push_back(fiveHealth);
	HealthAnimationData.images.push_back(fourHealth);
	HealthAnimationData.images.push_back(threeHealth);
	HealthAnimationData.images.push_back(twoHealth);
	HealthAnimationData.images.push_back(oneHealth);
	HealthAnimationData.images.push_back(zeroHealth);

	AnimatedSprite::setAnimData(&HealthAnimationData, 0);
}


LifeBar::~LifeBar() {
	SDL_Log("Destrucing Player");
}

void LifeBar::setLife(int health) {
	ChangeAnimation(health);
}

void LifeBar::update(double delta) {
	LifeBar::setLife(0);
}
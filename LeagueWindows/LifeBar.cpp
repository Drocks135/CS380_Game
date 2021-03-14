#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "LifeBar.hpp"
#include <SDL.h>

int health;
static AnimData PlayerAnimationData;

LifeBar::LifeBar() : AnimatedSprite("../assets/LifeBar.png", 1, 0) {
	health = 0;
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

	PlayerAnimationData.frameInfo.push_back(down);
	PlayerAnimationData.images.push_back(downRect);
	PlayerAnimationData.images.push_back(upRect);
	PlayerAnimationData.images.push_back(leftRect);
	PlayerAnimationData.images.push_back(rightRect);
	PlayerAnimationData.images.push_back(lastRect);

	AnimatedSprite::setAnimData(&PlayerAnimationData);
}

void LifeBar::up(double delta, bool start) {
	health += 1;
	if (health > 5) {
		health = 5;
	}
	
}

void LifeBar::down(double delta, bool start) {
	health -= 1;
	if (health < 0) {
		health = 0;
	}
	SDL_Log("Down Pressed");
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
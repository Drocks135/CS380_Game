#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "LifeBar.hpp"
#include <SDL.h>

LifeBar::LifeBar(Player* player) : AnimatedSprite("../assets/LifeBar.png", 1, 0) {
	this->player = player;
	currentHealth = this->player->getHealth();
	position.setX(0);
	position.setY(734);


	//start x, start y, width, height
	

	AnimData* HealthAnimationData = new AnimData();
	loadAnimData(*HealthAnimationData);
	AnimatedSprite::setAnimData(HealthAnimationData, 5);
}

void LifeBar::loadAnimData(AnimData& HealthAnimationData) {
	SDL_Rect* fiveHealth = new SDL_Rect{ 8, 8, 202, 34 };
	SDL_Rect* fourHealth = new SDL_Rect{ 8, 53, 202, 34 };
	SDL_Rect* threeHealth = new SDL_Rect{ 8, 96, 202, 34 };
	SDL_Rect* twoHealth = new SDL_Rect{ 8, 134, 202, 34 };
	SDL_Rect* oneHealth = new SDL_Rect{ 8, 171, 202, 34 };
	SDL_Rect* zeroHealth = new SDL_Rect{ 8, 209, 202, 34 };

	AnimFrameData* fiveHP = new AnimFrameData{ 0, 1 };
	AnimFrameData* fourHP = new AnimFrameData{ 1, 1 };
	AnimFrameData* threeHP = new AnimFrameData{ 2, 1 };
	AnimFrameData* twoHP = new AnimFrameData{ 3, 1 };
	AnimFrameData* oneHP = new AnimFrameData{ 4, 1 };
	AnimFrameData* zeroHP = new AnimFrameData{ 5, 1 };

	
	HealthAnimationData.images.push_back(zeroHealth);
	HealthAnimationData.images.push_back(oneHealth);
	HealthAnimationData.images.push_back(twoHealth);
	HealthAnimationData.images.push_back(threeHealth);
	HealthAnimationData.images.push_back(fourHealth);
	HealthAnimationData.images.push_back(fiveHealth);
	
	HealthAnimationData.frameInfo.push_back(fiveHP);
	HealthAnimationData.frameInfo.push_back(fourHP);
	HealthAnimationData.frameInfo.push_back(threeHP);
	HealthAnimationData.frameInfo.push_back(twoHP);
	HealthAnimationData.frameInfo.push_back(oneHP);
	HealthAnimationData.frameInfo.push_back(zeroHP);
}


LifeBar::~LifeBar() {
	SDL_Log("Destrucing Player");
}

void LifeBar::setLife() {
	if (currentHealth != player->getHealth()) {
		currentHealth = player->getHealth();
		ChangeAnimation(player->getHealth());
	}
}

void LifeBar::update(double delta) {
	LifeBar::setLife();
}
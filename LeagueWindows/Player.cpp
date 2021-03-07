#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "Player.hpp"
#include <SDL.h>

Player::Player(AnimData* inputAnimData) : AnimatedSprite("../assets/PlayerSpriteSheet.png", 1, inputAnimData, 0) {
	actionState = 0;
}


Player::~Player() {
	SDL_Log("Destrucing Player");
}

void Player::update(double delta) {
	if (velocity.getX() != 0 || velocity.getY() != 0) {
		UpdateAnimation(delta);
	}
	position.setX(position.getX() + velocity.getX() * delta);
	position.setY(position.getY() + velocity.getY() * delta);
	if (position.getX() > 1024 - rect->w || position.getX() < 0) {
		velocity.setX(0);
	}
	if (position.getY() > 768 - rect->h || position.getY() < 0) {
		velocity.setY(0);
	}
}

void Player::left(double delta, bool start) {
	int value = start ? -150 : 0;
	
	velocity.setX(velocity.getX() + value);
	
	

	if (start) {
		ChangeAnimation(2);
	}
}

void Player::right(double delta, bool start) {
	int value = start ? 150 : 0;
	
	velocity.setX(velocity.getX() + value);

	if (start) {
		ChangeAnimation(3);
	}
}

void Player::up(double delta, bool start) {
	int value = start && velocity.getY() > -150 ? -150 : 0;
	
	velocity.setY(value);

	if (start) {
		ChangeAnimation(1);
	}
}

void Player::down(double delta, bool start ) {
	int value = start && velocity.getY() < 150 ? 150 : 0;
	
	velocity.setY(value);

	if (start) {
		if(animNum != 0)
			ChangeAnimation(0);
	}
}

void Player::swingSword(double delta) {

}


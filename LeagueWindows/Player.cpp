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
	velocity.setX(value);
}

void Player::right(double delta, bool start) {
	int value = start ? 150 : 0;
	velocity.setX(value);
}

void Player::up(double delta, bool start) {
	int value = start ? -150 : 0;
	velocity.setY(value);
}

void Player::down(double delta, bool start ) {
	int value = start ? 150 : 0;
	velocity.setY(value);
}

void Player::swingSword(double delta) {

}


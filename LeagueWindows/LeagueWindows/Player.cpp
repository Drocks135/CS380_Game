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

}

void Player::left(double delta) {

}

void Player::right(double delta) {

}

void Player::up(double delta) {

}

void Player::down(double delta) {

}

void Player::swingSword(double delta) {

}


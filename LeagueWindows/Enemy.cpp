#include "Engine.hpp"
#include "Utility.hpp";
#include "AnimatedSprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <SDL.h>

Enemy::Enemy(AnimData* inputAnimData, Player* inputPlayer, Vector2 startPosition) : AnimatedSprite("../assets/EnemySpriteSheet.png", 1, inputAnimData, 0) {
	actionState = 0;
	currentImageScale = 1;

	currentPlayer = inputPlayer;

	position.setX(startPosition.getX());
	position.setY(startPosition.getY());
}


Enemy::~Enemy() {
	SDL_Log("Destrucing Enemy");
}

void Enemy::update(double delta) {

	// update velocity to track the player
	Vector3 playerPosition = currentPlayer->getPlayerPosition();

	int xVelocity = 0;
	int yVelocity = 0;

	int xDif = playerPosition.getX() - position.getX();
	int yDif = playerPosition.getY() - position.getY();

	if (playerPosition.getX() < position.getX()) {
		// prevent bug where enemy bounces back and forth
		// because it can't get to the player position
		if (xDif > -100)
			xVelocity = xDif;
		else
			xVelocity = -100;
	} 
	else if (playerPosition.getX() > position.getX()) {
		if (xDif < 100)
			xVelocity = xDif;
		else
			xVelocity = 100;
	}

	if (playerPosition.getY() < position.getY()) {
		if (yDif > -100)
			yVelocity = yDif;
		else
			yVelocity = -100;
	}
	else if (playerPosition.getY() > position.getY()) {
		if (yDif < 100)
			yVelocity = yDif;
		else
			yVelocity = 100;
	}

	velocity.setX(xVelocity);
	velocity.setY(yVelocity);

	// update position
	position.setX(position.getX() + velocity.getX() * delta);
	position.setY(position.getY() + velocity.getY() * delta);
}

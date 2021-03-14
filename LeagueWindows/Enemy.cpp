#include "Engine.hpp"
#include "Utility.hpp";
#include "AnimatedSprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <SDL.h>
#include <cmath>

// Enemy sprite is public domain, courtesy of  LazyDev (AKA Viktor Gorbulin).
// Link to sprite: https://opengameart.org/content/ghost-animated
Enemy::Enemy(AnimData* inputAnimData, Player* inputPlayer, Vector2 startPosition) : AnimatedSprite("../assets/EnemySpriteSheet.png", 1, inputAnimData, 0) {
	actionState = 0;
	currentImageScale = 3;

	currentPlayer = inputPlayer;

	position.setX(startPosition.getX());
	position.setY(startPosition.getY());

	// respawn position will be 200 units offscreen in the direction from the center it started from
	// so starting up and in the center  horizontally will respawn 200 units off screen vertically, cenetered
	// on the x axis, and so on
	if (position.getY() < 384) {
		respawnPosition.setY(-200);
		respawnPosition.setX(position.getX());
	}
	else if (position.getY() > 384) {
		respawnPosition.setY(968);
		respawnPosition.setX(position.getX());
	}
	// started in center, respawn to offscreen on the left/right
	else {
		if (respawnPosition.getX() < 512) {
			respawnPosition.setX(-200);
			respawnPosition.setY(position.getY());
		}
		else {
			respawnPosition.setX(1224);
			respawnPosition.setY(position.getY());
		}
	}

	flipDirection = SDL_FLIP_NONE;

	speed = 100;
}


Enemy::~Enemy() {
	SDL_Log("Destrucing Enemy");
}

void Enemy::update(double delta) {

	UpdateAnimation(delta);

	// update velocity to track the player
	Vector3 playerPosition = currentPlayer->getPlayerPosition();

	int xVelocity = 0;
	int yVelocity = 0;

	int xDif = playerPosition.getX() - position.getX();
	int yDif = playerPosition.getY() - position.getY();

	// TODO: FIX THIS SO THAT IT DIES WHEN IT GETS HIT BY THE SWORDS
	if (std::abs(xDif) < 20 && std::abs(yDif) < 20) {
		Die();
	}

	if (playerPosition.getX() < position.getX()) {
		// prevent bug where enemy bounces back and forth
		// because it can't get to the player position
		if (xDif > -speed)
			xVelocity = xDif;
		else
			xVelocity = -speed;

		// flip the sprite to face the player
		flipDirection = SDL_FLIP_HORIZONTAL;
	} 
	else if (playerPosition.getX() > position.getX()) {
		if (xDif < speed)
			xVelocity = xDif;
		else
			xVelocity = speed;

		// flip the sprite to face the player
		flipDirection = SDL_FLIP_NONE;
	}

	if (playerPosition.getY() < position.getY()) {
		if (yDif > -speed)
			yVelocity = yDif;
		else
			yVelocity = -speed;
	}
	else if (playerPosition.getY() > position.getY()) {
		if (yDif < speed)
			yVelocity = yDif;
		else
			yVelocity = speed;
	}

	

	velocity.setX(xVelocity);
	velocity.setY(yVelocity);

	// update position
	position.setX(position.getX() + velocity.getX() * delta);
	position.setY(position.getY() + velocity.getY() * delta);
}

// overrides animatedsprite to make use of RenderCopyEx to flip our sprite
void Enemy::draw() {
	SDL_Rect* dst = new SDL_Rect();
	dst->x = position.getX();
	dst->y = position.getY();
	dst->w = currentImage->w * currentImageScale;
	dst->h = currentImage->h * currentImageScale;
	SDL_RenderCopyEx(Engine::getRenderer(), texture, currentImage, dst, 0.0, NULL, flipDirection);
}

// move enemy offscreen to its respawn point
void Enemy::Die() {
	position = respawnPosition;
}

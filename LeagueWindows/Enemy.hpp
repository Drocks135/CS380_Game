#ifndef			__HPP__ENEMY__
#define			__HPP__ENEMY__

#include "AnimatedSprite.hpp"
#include "Utility.hpp"
#include "Player.hpp"
#include <SDL.h>
#include <cmath>

class Enemy : public AnimatedSprite {
public:
	Enemy(AnimData* inputAnimData, Player* inputPlayer, Vector2 startPosition);
	~Enemy();
	void update(double delta);
	void draw();

private:
	Player* currentPlayer;
	// we'll flip the sprite depending on whether we're facing left or right
	SDL_RendererFlip flipDirection;

	int speed;
	Vector3 respawnPosition;

	void Die();
};

#endif
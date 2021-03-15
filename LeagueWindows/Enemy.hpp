#ifndef			__HPP__ENEMY__
#define			__HPP__ENEMY__

#include "AnimatedSprite.hpp"
#include "Utility.hpp"
#include "Player.hpp"
#include <SDL.h>
#include <cmath>

// Class for our enemies. All an enemy really does is 
// try to move towards the player if they are able to.
// When an enemy "dies" they don't actually despawn - 
// rather, they are moved offscreen, where they then 
// try to attack the player once more. This makes consistent
// spawning of enemies more simplistic
class Enemy : public AnimatedSprite {
public:
	Enemy(AnimData* inputAnimData, Player* inputPlayer, Vector2* startPosition);
	~Enemy();
	void update(double delta);
	void draw();

private:
	// Included to track player's position
	Player* currentPlayer;

	// we'll flip the sprite depending on whether we're facing left or right
	SDL_RendererFlip flipDirection;

	// the speed the enemy moves
	int speed;

	// the location the enemy will "respawn" at on death
	Vector3 respawnPosition;

	void Die();
};

#endif
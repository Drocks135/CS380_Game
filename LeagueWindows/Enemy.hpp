#ifndef			__HPP__ENEMY__
#define			__HPP__ENEMY__

#include "AnimatedSprite.hpp"
#include "Utility.hpp"
#include "Player.hpp"
#include <SDL.h>

class Enemy : public AnimatedSprite {
public:
	Enemy(AnimData* inputAnimData, Player* inputPlayer, Vector2 startPosition);
	~Enemy();
	void update(double delta);

private:
	Player* currentPlayer;
};

#endif
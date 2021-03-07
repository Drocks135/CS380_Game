#ifndef			__HPP__PLAYER__
#define			__HPP__PLAYER__

#include "AnimatedSprite.hpp"
#include "Utility.hpp"
#include <SDL.h>

class Player : public AnimatedSprite {
public:
	Player(AnimData* inputAnimData);
	~Player();
	void update(double delta);
	void left(double delta);
	void right(double delta);
	void up(double delta);
	void down(double delta);
	void swingSword(double delta);
};

#endif
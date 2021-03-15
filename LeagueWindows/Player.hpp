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
	void left(double delta, bool start);
	void right(double delta, bool start);
	void up(double delta, bool start);
	void down(double delta, bool start);
	void swingSword(double delta);
};

#endif
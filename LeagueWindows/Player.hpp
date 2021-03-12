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

private: 
	bool movingDown;
	bool movingUp;
	bool movingLeft;
	bool movingRight;
	void EndAnimationBasedOnMovement(int animationEnding);
	void CheckAndSetDownAnim();
	void CheckAndSetUpAnim();
	void CheckAndSetLeftAnim();
	void CheckAndSetRightAnim();

};

#endif
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
	void left(double delta, bool keydown);
	void right(double delta, bool keydown);
	void up(double delta, bool keydown);
	void down(double delta, bool keydown);
	void swingSword(double delta, bool keydown);
	void incrementScore();
	int getScore();
	int getHealth();
	Vector3 getPlayerPosition();

private: 
	int health;
	int score;
	bool movingDown;
	bool movingUp;
	bool movingLeft;
	bool movingRight;
	// indicates how long a swing will take
	double swingTimer;
	// indicates whether we're in a sword swing. movement
	// will stop when this is occuring
	bool swingingSword;

	int playerSpeed;

	void EndAnimationBasedOnMovement(int animationEnding);
	void CheckAndSetDownAnim();
	void CheckAndSetUpAnim();
	void CheckAndSetLeftAnim();
	void CheckAndSetRightAnim();

};

#endif
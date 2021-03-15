#ifndef			__HPP__PLAYER__
#define			__HPP__PLAYER__

#include "AnimatedSprite.hpp"
#include "Utility.hpp"
#include <functional>
#include <SDL.h>

// The game's player class. Contains logic for all game input,
// as well as keeping track of game logic such as health and score.
class Player : public AnimatedSprite {
public:
	Player();
	~Player();
	void update(double delta);

	// Player actions (how the player is controlled)
	void left(double delta, bool keydown);
	void right(double delta, bool keydown);
	void up(double delta, bool keydown);
	void down(double delta, bool keydown);
	void swingSword(double delta, bool keydown);

	void incrementScore();
	void takeDamage();

	int getScore();
	int getHealth();

	SDL_Rect* getSwordHitbox();
	
	Vector3 getPlayerPosition();

	SDL_Rect* getPlayerHitbox();
	

private: 
	// player game logic variables
	int health;
	int score;

	// track player movement states
	bool movingDown;
	bool movingUp;
	bool movingLeft;
	bool movingRight;

	// indicates how long a swing will take
	double swingTimer;
	double invincibilityTimer;

	// hitbox for sword
	SDL_Rect* swordHitbox;

	// indicates whether we're in a sword swing. movement
	// will stop when this is occuring
	bool swingingSword;

	// movment speed of the player
	int playerSpeed;




	void loadAnimData(AnimData& PlayerAnimationData);
	// animation logic helpers for player movement
	void EndAnimationBasedOnMovement(int animationEnding);
	void CheckAndSetDownAnim();
	void CheckAndSetUpAnim();
	void CheckAndSetLeftAnim();
	void CheckAndSetRightAnim();

};

#endif
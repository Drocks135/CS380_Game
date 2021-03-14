#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "Utility.hpp";
#include "Player.hpp"
#include <SDL.h>
#include <string>

#define DOWN_ANIM 0
#define UP_ANIM 1
#define LEFT_ANIM 2
#define RIGHT_ANIM 3

#define DOWN_SWING_ANIM 4
#define UP_SWING_ANIM 5
#define LEFT_SWING_ANIM 6
#define RIGHT_SWING_ANIM 7

// Player sprite is courtesy of Calciumtrice (via https://opengameart.org/content/simple-knight) and usable under 
// the Creative Commons Attribution 3.0 license. No modifications to the sprites have been made.
// Attribution notice from the website: Simple Knight by Calciumtrice, usable under Creative Commons Attribution 3.0 license.
Player::Player(AnimData* inputAnimData) : AnimatedSprite("../assets/PlayerSpriteSheet.png", 1, inputAnimData, 0) {
	// scale our sprites to fit well within our screen
	currentImageScale = 3;

	movingDown = false;
	movingUp = false;
	movingLeft = false;
	movingRight = false;

	swingTimer = 0.0;
	swingingSword = false;

	health = 5;
	score = 0;

	playerSpeed = 150;

	// start player near the center of the screen
	position.setX(480);
	position.setY(300);
}


Player::~Player() {
	// destruction mostly taken care of in sprite
}

void Player::update(double delta) {

	// check status of the sword swing - either branch will only 
	// run if a sword swing has recently occured
	// if the sword swing is in progress
	if (swingingSword && swingTimer > 0) {
		swingTimer -= delta;
	}
	// if the sword swing is over
	else if (swingingSword) {
		// if we're done, update the flags and animation to facing the correct direction
		swingingSword = false;
		swingTimer = 0.0;
		
		// movement animations are swing animations - 4
		// shouldn't need the else, but there just in case
		if (animNum > 3)
			ChangeAnimation(animNum - 4);
		else {
			// change animation to the correct direction based on movement
			if (movingUp)
				ChangeAnimation(UP_ANIM);
			else if (movingDown)
				ChangeAnimation(DOWN_ANIM);
			else if (movingLeft)
				ChangeAnimation(LEFT_ANIM);
			else if (movingRight)
				ChangeAnimation(RIGHT_ANIM);
		}
	}
	
	// lock movement if we're swinging the sword
	if (!swingingSword) {
		// caclculate movement based on input states
		int xVelocity = 0;
		int yVelocity = 0;

		if (movingDown)
			yVelocity += playerSpeed;
		if (movingUp)
			yVelocity += -playerSpeed;
		if (movingRight)
			xVelocity += playerSpeed;
		if (movingLeft)
			xVelocity += -playerSpeed;

		velocity.setX(xVelocity);
		velocity.setY(yVelocity);
	}

	// unless we're doing a sword swing, update animation only when we're moving
	if (swingingSword) {
		UpdateAnimation(delta);
	}

	if (velocity.getX() != 0 || velocity.getY() != 0) {
		UpdateAnimation(delta);
	}

	// update position
	position.setX(position.getX() + velocity.getX() * delta);
	position.setY(position.getY() + velocity.getY() * delta);

	//  Add collision at screen edge
	if (position.getX() > 1024 - currentImage->w * currentImageScale) {
		position.setX(1024 - currentImage->w * currentImageScale);
	}
	else if (position.getX() < 0) {
		position.setX(0);
	}
	if (position.getY() > 768 - currentImage->h * currentImageScale) {
		position.setY(768 - currentImage->h * currentImageScale);
	}
	else if (position.getY() < 0) {
		position.setY(0);
	}
}

// all movment functions have the same sort of flow:
// if the key is being pressed down, set the flag for moving in that 
// direction to true, and update the animation to that direction (unless
// we are swinging the sword, moving in the opposite direction, or already
// moving in that direction
// if the key has been lifted, unset the flag and end our animation (see helper function)
void Player::left(double delta, bool keydown) {
	if (keydown) {
		movingLeft = true;
		if(animNum != LEFT_ANIM && !movingRight && !swingingSword)
			ChangeAnimation(LEFT_ANIM);
	}
	else {
		movingLeft = false;
		EndAnimationBasedOnMovement(LEFT_ANIM);
	}
}

void Player::right(double delta, bool keydown) {
	if (keydown) {
		movingRight = true;
		if(animNum != RIGHT_ANIM && !movingLeft && !swingingSword)
			ChangeAnimation(RIGHT_ANIM);
	}
	else {
		movingRight = false;
		EndAnimationBasedOnMovement(RIGHT_ANIM);
	}
}

void Player::up(double delta, bool keydown) {
	if (keydown) {
		movingUp = true;
		if(animNum != UP_ANIM && !movingDown && !swingingSword)
			ChangeAnimation(UP_ANIM);
	}
	else {
		movingUp = false;
		EndAnimationBasedOnMovement(UP_ANIM);
	}
}

void Player::down(double delta, bool keydown ) {
	if (keydown) {
		movingDown = true;
		if(animNum != DOWN_ANIM && !movingUp && !swingingSword)
			ChangeAnimation(DOWN_ANIM);
	}
	else {
		movingDown = false;
		EndAnimationBasedOnMovement(DOWN_ANIM);
	}
}

// swings the player's sword
void Player::swingSword(double delta, bool keydown) {
	if (!swingingSword) {
		// we will swing in the direction of the current animation
		// swing animation number for all directions is current animation + 4
		ChangeAnimation(animNum + 4);
		swingingSword = true;
		swingTimer = 0.42;

		velocity.setX(0);
		velocity.setY(0);
	}
}

// score can only go up or be reset, and only rises in increments of 100
void Player::incrementScore() {
	score += 100;
}

// included so that the HUD can display the score
int Player::getScore() {
	return score;
}

// included so that enemies can track the player
Vector3 Player::getPlayerPosition() {
	return this->position;
}

// included so that the health bar HUD can track player heatlth
int Player::getHealth() {
	return this->health;
}

void Player::EndAnimationBasedOnMovement(int animationEnding) {
	// checks for movement on each of the axes to see which animation to display next.
	// if there is movement in the opposite direction of the animation that is ending
	// (e.g. down movement when up movment ends) the animation will be set to that.
	// otherwise, animation will be set to either of the directions on the perpendicular
	// axis. 

	// If there is no movement elsewhere, the animation will stay in its current state. 
	if (animationEnding == UP_ANIM) {
		CheckAndSetDownAnim();
		CheckAndSetLeftAnim();
		CheckAndSetRightAnim();
	}
	else if (animationEnding == DOWN_ANIM) {
		CheckAndSetUpAnim();
		CheckAndSetLeftAnim();
		CheckAndSetRightAnim();
	}
	else if (animationEnding == RIGHT_ANIM) {
		CheckAndSetLeftAnim();
		CheckAndSetUpAnim();
		CheckAndSetDownAnim();
	}
	else if (animationEnding == LEFT_ANIM) {
		CheckAndSetRightAnim();
		CheckAndSetUpAnim();
		CheckAndSetDownAnim();
	}
}


// helper functions that set an animation in the 
// correct direction if the player is moving in 
// that direction
void Player::CheckAndSetDownAnim() {
	if (movingDown)
		ChangeAnimation(DOWN_ANIM);
}

void Player::CheckAndSetUpAnim() {
	if(movingUp)
		ChangeAnimation(UP_ANIM);
}

void Player::CheckAndSetLeftAnim() {
	if (movingLeft)
		ChangeAnimation(LEFT_ANIM);
}

void Player::CheckAndSetRightAnim() {
	if (movingRight)
		ChangeAnimation(RIGHT_ANIM);
}

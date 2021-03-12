#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "Utility.hpp";
#include "Player.hpp"
#include <SDL.h>

#define DOWN_ANIM 0
#define UP_ANIM 1
#define LEFT_ANIM 2
#define RIGHT_ANIM 3

Player::Player(AnimData* inputAnimData) : AnimatedSprite("../assets/PlayerSpriteSheet.png", 1, inputAnimData, 0) {
	actionState = 0;
	currentImageScale = 3;

	movingDown = false;
	movingUp = false;
	movingLeft = false;
	movingRight = false;

	health = 5;
}


Player::~Player() {
	SDL_Log("Destrucing Player");
}

void Player::update(double delta) {

	// caclculate movement based on input states
	int xVelocity = 0;
	int yVelocity = 0;

	if (movingDown)
		yVelocity += 150;
	if (movingUp)
		yVelocity += -150;
	if (movingRight)
		xVelocity += 150;
	if (movingLeft)
		xVelocity += -150;

	velocity.setX(xVelocity);
	velocity.setY(yVelocity);

	// update animations
	if (velocity.getX() != 0 || velocity.getY() != 0) {
		UpdateAnimation(delta);
	}

	// update position
	position.setX(position.getX() + velocity.getX() * delta);
	position.setY(position.getY() + velocity.getY() * delta);

	//  Add collision at screen edge TODO FIX TO ACTUAL DRAWN SIZE
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

// included so that enemies can track the player
Vector3 Player::getPlayerPosition() {
	return this->position;
}

int Player::getHealth() {
	return this->health;
}


void Player::left(double delta, bool keydown) {
	if (keydown) {
		movingLeft = true;
		if(animNum != LEFT_ANIM && !movingRight)
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
		if(animNum != RIGHT_ANIM && !movingLeft)
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
		if(animNum != UP_ANIM && !movingDown)
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
		if(animNum != DOWN_ANIM && !movingUp)
			ChangeAnimation(DOWN_ANIM);
	}
	else {
		movingDown = false;
		EndAnimationBasedOnMovement(DOWN_ANIM);
	}
}

void Player::swingSword(double delta) {

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

#include "Engine.hpp"
#include "AnimatedSprite.hpp"
#include "Utility.hpp";
#include "Player.hpp"
#include <SDL.h>
#include <string>
#include <functional>

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
Player::Player() : AnimatedSprite("../assets/PlayerSpriteSheet.png", 1, 0) {
	// scale our sprites to fit well within our screen
	currentImageScale = 3;

	movingDown = false;
	movingUp = false;
	movingLeft = false;
	movingRight = false;

	swingTimer = 0.0;
	invincibilityTimer = 0.0;
	swingingSword = false;

	swordHitbox = new SDL_Rect{ 0, 0, 0, 0 };

	health = 5;
	score = 0;

	playerSpeed = 150;

	// start player near the center of the screen
	position.setX(480);
	position.setY(300);

	AnimData* PlayerAnimData = new AnimData();
	loadAnimData(*PlayerAnimData);
	AnimatedSprite::setAnimData(PlayerAnimData, 0);
}

Player::~Player() {
	// destruction mostly taken care of in sprite
}

void Player::loadAnimData(AnimData &PlayerAnimationData) {
	AnimFrameData* down = new AnimFrameData{ 0, 5 };
	AnimFrameData* up = new AnimFrameData{ 5, 5 };
	AnimFrameData* left = new AnimFrameData{ 10, 5 };
	AnimFrameData* right = new AnimFrameData{ 15, 5 };

	AnimFrameData* downSwing = new AnimFrameData{ 20, 5 };
	AnimFrameData* upSwing = new AnimFrameData{ 25, 5 };
	AnimFrameData* leftSwing = new AnimFrameData{ 30, 5 };
	AnimFrameData* rightSwing = new AnimFrameData{ 35, 5 };

	SDL_Rect* downRect1 = new SDL_Rect{ 4, 4, 18, 25 };
	SDL_Rect* downRect2 = new SDL_Rect{ 35, 4, 18, 25 };
	SDL_Rect* downRect3 = new SDL_Rect{ 67, 4, 18, 25 };
	SDL_Rect* downRect4 = new SDL_Rect{ 99, 4, 18, 25 };
	SDL_Rect* downRect5 = new SDL_Rect{ 131, 4, 18, 25 };

	SDL_Rect* upRect1 = new SDL_Rect{ 10, 35, 18, 25 };
	SDL_Rect* upRect2 = new SDL_Rect{ 42, 35, 18, 25 };
	SDL_Rect* upRect3 = new SDL_Rect{ 74, 35, 18, 25 };
	SDL_Rect* upRect4 = new SDL_Rect{ 106, 35, 18, 25 };
	SDL_Rect* upRect5 = new SDL_Rect{ 138, 35, 18, 25 };

	SDL_Rect* leftRect1 = new SDL_Rect{ 3, 67, 18, 25 };
	SDL_Rect* leftRect2 = new SDL_Rect{ 35, 67, 18, 25 };
	SDL_Rect* leftRect3 = new SDL_Rect{ 68, 67, 18, 25 };
	SDL_Rect* leftRect4 = new SDL_Rect{ 99, 67, 18, 25 };
	SDL_Rect* leftRect5 = new SDL_Rect{ 132, 67, 18, 25 };
	SDL_Rect* rightRect1 = new SDL_Rect{ 11, 99, 18, 25 };
	SDL_Rect* rightRect2 = new SDL_Rect{ 43, 99, 18, 25 };
	SDL_Rect* rightRect3 = new SDL_Rect{ 75, 99, 18, 25 };
	SDL_Rect* rightRect4 = new SDL_Rect{ 107, 99, 18, 25 };
	SDL_Rect* rightRect5 = new SDL_Rect{ 139, 99, 18, 25 };

	SDL_Rect* downSwingRect1 = new SDL_Rect{ 4, 131, 18, 25 };
	SDL_Rect* downSwingRect2 = new SDL_Rect{ 43, 131, 13, 25 };
	SDL_Rect* downSwingRect3 = new SDL_Rect{ 76, 131, 17, 25 };
	SDL_Rect* downSwingRect4 = new SDL_Rect{ 96, 131, 26, 25 };
	SDL_Rect* downSwingRect5 = new SDL_Rect{ 128, 131, 22, 25 };

	SDL_Rect* upSwingRect1 = new SDL_Rect{ 10, 163, 18, 25 };
	SDL_Rect* upSwingRect2 = new SDL_Rect{ 39, 163, 15, 25 };
	SDL_Rect* upSwingRect3 = new SDL_Rect{ 67, 163, 17, 25 };
	SDL_Rect* upSwingRect4 = new SDL_Rect{ 103, 163, 25 , 25 };
	SDL_Rect* upSwingRect5 = new SDL_Rect{ 138, 163, 22 , 25 };

	SDL_Rect* leftSwingRect1 = new SDL_Rect{ 3, 196, 18, 25 };
	SDL_Rect* leftSwingRect2 = new SDL_Rect{ 43, 196, 14, 25 };
	SDL_Rect* leftSwingRect3 = new SDL_Rect{ 75, 196, 19, 25 };
	SDL_Rect* leftSwingRect4 = new SDL_Rect{ 96, 196, 27, 25 };
	SDL_Rect* leftSwingRect5 = new SDL_Rect{ 128, 196, 22, 25 };

	SDL_Rect* rightSwingRect1 = new SDL_Rect{ 11, 227, 18, 25 };
	SDL_Rect* rightSwingRect2 = new SDL_Rect{ 39, 227, 14, 25 };
	SDL_Rect* rightSwingRect3 = new SDL_Rect{ 66, 227, 19, 25 };
	SDL_Rect* rightSwingRect4 = new SDL_Rect{ 101, 227, 27, 25 };
	SDL_Rect* rightSwingRect5 = new SDL_Rect{ 138, 227, 22, 25 };

	PlayerAnimationData.frameInfo.push_back(down);
	PlayerAnimationData.frameInfo.push_back(up);
	PlayerAnimationData.frameInfo.push_back(left);
	PlayerAnimationData.frameInfo.push_back(right);
	PlayerAnimationData.frameInfo.push_back(downSwing);
	PlayerAnimationData.frameInfo.push_back(upSwing);
	PlayerAnimationData.frameInfo.push_back(leftSwing);
	PlayerAnimationData.frameInfo.push_back(rightSwing);

	PlayerAnimationData.images.push_back(downRect1);
	PlayerAnimationData.images.push_back(downRect2);
	PlayerAnimationData.images.push_back(downRect3);
	PlayerAnimationData.images.push_back(downRect4);
	PlayerAnimationData.images.push_back(downRect5);

	PlayerAnimationData.images.push_back(upRect1);
	PlayerAnimationData.images.push_back(upRect2);
	PlayerAnimationData.images.push_back(upRect3);
	PlayerAnimationData.images.push_back(upRect4);
	PlayerAnimationData.images.push_back(upRect5);

	PlayerAnimationData.images.push_back(leftRect1);
	PlayerAnimationData.images.push_back(leftRect2);
	PlayerAnimationData.images.push_back(leftRect3);
	PlayerAnimationData.images.push_back(leftRect4);
	PlayerAnimationData.images.push_back(leftRect5);

	PlayerAnimationData.images.push_back(rightRect1);
	PlayerAnimationData.images.push_back(rightRect2);
	PlayerAnimationData.images.push_back(rightRect3);
	PlayerAnimationData.images.push_back(rightRect4);
	PlayerAnimationData.images.push_back(rightRect5);

	PlayerAnimationData.images.push_back(downSwingRect1);
	PlayerAnimationData.images.push_back(downSwingRect2);
	PlayerAnimationData.images.push_back(downSwingRect3);
	PlayerAnimationData.images.push_back(downSwingRect4);
	PlayerAnimationData.images.push_back(downSwingRect5);

	PlayerAnimationData.images.push_back(upSwingRect1);
	PlayerAnimationData.images.push_back(upSwingRect2);
	PlayerAnimationData.images.push_back(upSwingRect3);
	PlayerAnimationData.images.push_back(upSwingRect4);
	PlayerAnimationData.images.push_back(upSwingRect5);

	PlayerAnimationData.images.push_back(leftSwingRect1);
	PlayerAnimationData.images.push_back(leftSwingRect2);
	PlayerAnimationData.images.push_back(leftSwingRect3);
	PlayerAnimationData.images.push_back(leftSwingRect4);
	PlayerAnimationData.images.push_back(leftSwingRect5);

	PlayerAnimationData.images.push_back(rightSwingRect1);
	PlayerAnimationData.images.push_back(rightSwingRect2);
	PlayerAnimationData.images.push_back(rightSwingRect3);
	PlayerAnimationData.images.push_back(rightSwingRect4);
	PlayerAnimationData.images.push_back(rightSwingRect5);
}

void Player::update(double delta) {

	// Make the player invincible for a little bit after getting hurt
	if (invincibilityTimer > 0) {
		if (delta > invincibilityTimer)
			invincibilityTimer = 0;
		else
			invincibilityTimer -= delta;
	}

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

void Player::takeDamage() {
	if (invincibilityTimer == 0 && health > 0) {
		invincibilityTimer = 2.0;
		health--;
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

SDL_Rect* Player::getPlayerHitbox() {
	return currentImage;
}

SDL_Rect* Player::getSwordHitbox() {
	if (animNum == DOWN_SWING_ANIM) {
		
		swordHitbox->x = this->position.getX() - 15;
		swordHitbox->y = this->position.getY() + this->currentImage->w;
		swordHitbox->w = this->currentImage->w + 30;
		swordHitbox->h = 75;
	}
	else if (animNum == UP_SWING_ANIM) {
		swordHitbox->x = this->position.getX() - 15;
		swordHitbox->y = this->position.getY() - 50;
		swordHitbox->w = this->currentImage->w + 30;
		swordHitbox->h = 75;
	}
	else if (animNum == LEFT_SWING_ANIM) {
		swordHitbox->x = this->position.getX() - 50;
		swordHitbox->y = this->position.getY() - 15;
		swordHitbox->w = 75;
		swordHitbox->h = this->currentImage->h + 30;
	}
	else if (animNum == RIGHT_SWING_ANIM) {
		swordHitbox->x = this->position.getX() + this->currentImage->w;
		swordHitbox->y = this->position.getY() - 15;
		swordHitbox->w = 75;
		swordHitbox->h = this->currentImage->h + 30;

	}
	else{
		swordHitbox->x = 0;
		swordHitbox->y = 0;
		swordHitbox->w = 0;
		swordHitbox->h = 0; 
	}
	
	return swordHitbox;
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

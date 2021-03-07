#include "Engine.hpp"
#include "Banana.hpp"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"
#include "Player.hpp"
#include "HUD.hpp"
#include <SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv){
	SDL_Log("Starting up, with following arguments:");
	for(int i=0; i<argc; ++i){
		SDL_Log("%d = %s", i, argv[i]);
	}

	// Create a scene
	Scene one;
	// Create an engine.  Must happen early, creates the renderer.
	Engine engine(1024, 768);

	// Add the HUD
	HUD* h = new HUD();
	one.addUpdateable(h);
	one.addDrawable(h);


	/*// code taken from the textbook
	struct AnimFrameData {
		// The index of the first frame of an animation
		int startFrame;
		// The total number of frames for a particulare animation
		int numFrames;
	};

	struct AnimData {
		// Array of images for all animations for a sprite
		std::vector<SDL_Rect*> images;
		// Frame data array for each of the animations for the sprite
		std::vector<AnimFrameData> frameInfo;
	};*/

	// Construct animation structs for the player object
	// TODO: MAKE STATIC METHOD IN PLAYER TO DO THIS
	AnimFrameData down;
	down.startFrame = 0;
	down.numFrames = 1;

	AnimFrameData up;
	up.startFrame = 1;
	up.numFrames = 1;

	AnimFrameData left;
	left.startFrame = 2;
	left.numFrames = 1;

	AnimFrameData right;
	right.startFrame = 3;
	right.numFrames = 1;

	

	SDL_Rect* downRect = new SDL_Rect{ 4, 3, 18, 25 };
	SDL_Rect* upRect = new SDL_Rect{10, 35, 17, 24};
	SDL_Rect* leftRect = new SDL_Rect{ 3, 67, 18, 25 };
	SDL_Rect* rightRect = new SDL_Rect{ 11, 99, 18, 25 };

	AnimData PlayerAnimationData;
	PlayerAnimationData.frameInfo.push_back(down);
	PlayerAnimationData.frameInfo.push_back(up);
	PlayerAnimationData.frameInfo.push_back(left);
	PlayerAnimationData.frameInfo.push_back(right);
	PlayerAnimationData.images.push_back(downRect);
	PlayerAnimationData.images.push_back(upRect);
	PlayerAnimationData.images.push_back(leftRect);
	PlayerAnimationData.images.push_back(rightRect);

	Player* player = new Player(&PlayerAnimationData);

	auto player_up = [player](double delta, bool start) { player->up(delta, start); };
	auto player_down = [player](double delta, bool start) { player->down(delta, start); };
	auto player_left = [player](double delta, bool start) { player->left(delta, start); };
	auto player_right = [player](double delta, bool start) { player->right(delta, start); };
	
	one.addUpdateable(player);
	one.addDrawable(player);

	one.addKeyEvent(SDLK_w, player_up);
	one.addKeyEvent(SDLK_a, player_left);
	one.addKeyEvent(SDLK_d, player_right);
	one.addKeyEvent(SDLK_s, player_down);

	// Set the scene in the engine
	engine.setScene(&one);
	
	// Get the engine running.
	engine.run();

	return 0;
}

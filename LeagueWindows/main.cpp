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

	// Construct animation structs for the player object
	// TODO: MAKE STATIC METHOD IN PLAYER TO DO THIS
	AnimFrameData* down = new AnimFrameData{ 0, 5 };

	AnimFrameData* up = new AnimFrameData{ 5, 5 };


	AnimFrameData* left = new AnimFrameData{ 10, 5 };


	AnimFrameData* right = new AnimFrameData{ 15, 1 };

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
	SDL_Rect* rightRect = new SDL_Rect{ 11, 99, 18, 25 };

	AnimData PlayerAnimationData;
	PlayerAnimationData.frameInfo.push_back(down);
	PlayerAnimationData.frameInfo.push_back(up);
	PlayerAnimationData.frameInfo.push_back(left);
	PlayerAnimationData.frameInfo.push_back(right);
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

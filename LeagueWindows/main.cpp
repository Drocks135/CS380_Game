#include "Engine.hpp"
#include "Banana.hpp"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
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

	AnimData PlayerAnimationData;
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

	

	Player* player = new Player(&PlayerAnimationData);

	auto player_up = [player](double delta, bool start) { player->up(delta, start); };
	auto player_down = [player](double delta, bool start) { player->down(delta, start); };
	auto player_left = [player](double delta, bool start) { player->left(delta, start); };
	auto player_right = [player](double delta, bool start) { player->right(delta, start); };
	auto player_swing = [player](double delta, bool start) { player->swingSword(delta, start); };
	
	one.addUpdateable(player);
	one.addDrawable(player);

	one.addKeyEvent(SDLK_w, player_up);
	one.addKeyEvent(SDLK_a, player_left);
	one.addKeyEvent(SDLK_d, player_right);
	one.addKeyEvent(SDLK_s, player_down);
	one.addKeyEvent(SDLK_SPACE, player_swing);

	// make enemy animation structs
	AnimFrameData* enemyFrameData = new AnimFrameData{ 0, 1 };
	AnimData enemyAnimationData;
	enemyAnimationData.frameInfo.push_back(enemyFrameData);
	enemyAnimationData.images.push_back(new SDL_Rect{ 0, 0, 100, 100 });

	Vector2* startpos = new Vector2(200, 200);

	Enemy* enemy = new Enemy(&enemyAnimationData, player, *startpos);

	//one.addDrawable(enemy);
	//one.addUpdateable(enemy);

	// Set the scene in the engine
	engine.setScene(&one);
	
	// Get the engine running.
	engine.run();

	return 0;
}

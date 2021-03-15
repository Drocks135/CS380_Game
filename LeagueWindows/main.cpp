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
#include "Background.hpp"
#include "LifeBar.hpp"

int main(int argc, char** argv){
	SDL_Log("Starting up, with following arguments:");
	for(int i=0; i<argc; ++i){
		SDL_Log("%d = %s", i, argv[i]);
	}

	// Create a scene
	Scene one;
	// Create an engine.  Must happen early, creates the renderer.
	Engine engine(1024, 768);

	Background* background = new Background();
	one.addUpdateable(background);
	one.addDrawable(background);

	Player* player = new Player();

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
	AnimFrameData* enemyMovementFrameData = new AnimFrameData{ 0, 4 };
	AnimData enemyAnimationData;
	enemyAnimationData.frameInfo.push_back(enemyMovementFrameData);

	SDL_Rect* enemyMove1 = new SDL_Rect{ 0, 64, 32, 32 };
	SDL_Rect* enemyMove2 = new SDL_Rect{ 32, 64, 32, 32 };
	SDL_Rect* enemyMove3 = new SDL_Rect{ 64, 64, 32, 32 };
	SDL_Rect* enemyMove4 = new SDL_Rect{ 96, 64, 32, 32 };

	enemyAnimationData.images.push_back(enemyMove1);
	enemyAnimationData.images.push_back(enemyMove2);
	enemyAnimationData.images.push_back(enemyMove3);
	enemyAnimationData.images.push_back(enemyMove4);



	Vector2* startpos1 = new Vector2(500, 100);
	Vector2* startpos2 = new Vector2(20, 668);
	Vector2* startpos3 = new Vector2(900, 668);

	Enemy* enemy1 = new Enemy(&enemyAnimationData, player, startpos1);
	Enemy* enemy2 = new Enemy(&enemyAnimationData, player, startpos2);
	Enemy* enemy3 = new Enemy(&enemyAnimationData, player, startpos3);

	one.addDrawable(enemy1);
	one.addUpdateable(enemy1);
	one.addDrawable(enemy2);
	one.addUpdateable(enemy2);
	one.addDrawable(enemy3);
	one.addUpdateable(enemy3);

	// Add the HUD
	HUD* h = new HUD(player);
	one.addUpdateable(h);
	one.addDrawable(h);

	LifeBar* playerHealth = new LifeBar();
	one.addDrawable(playerHealth);
	one.addUpdateable(playerHealth);


	// Set the scene in the engine
	engine.setScene(&one);
	
	// Get the engine running.
	engine.run();

	return 0;
}

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
	AnimFrameData afd;
	afd.startFrame = 0;
	afd.numFrames = 10;

	SDL_Rect* anim1Rect = new SDL_Rect();

	AnimData PlayerAnimationData;
	PlayerAnimationData.frameInfo.push_back(afd);
	PlayerAnimationData.images.push_back(anim1Rect);
	

	std::cout << "AnimFrame data is " << afd.startFrame << afd.numFrames << std::endl;

	Player* player = new Player(&PlayerAnimationData);


	/*auto player_up = [player](double delta) { player->up(delta); };
	auto player_down = [player](double delta) { player->down(delta); };
	auto player_left = [player](double delta) { player->left(delta); };*/
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

	/*// Make a banana and add to scene. Should update and draw.
	SDL_Surface* surface = IMG_Load("../assets/banana.png");
	//Banana* b = new Banana();
	//Sprite* b = new Sprite(surface, 3);
	//Sprite* other = new Sprite(surface, 1);
	Banana* b = new Banana();
	Banana* b2 = new Banana();
	delete b2;

	b->setLayer(2);


	std::cout << "Result is: " << b->getLayer() << std::endl;
	//Banana* b = new Banana();
	one.addUpdateable(b);
	one.addDrawable(b);
	auto b_up = [b](double delta) { b->up(delta); };
	auto b_down = [b](double delta) { b->down(delta); };
	auto b_left = [b](double delta) { b->left(delta); };
	auto b_right = [b](double delta) { b->right(delta); };
	one.addKeyEvent( SDLK_w, b_up );
	one.addKeyEvent( SDLK_a, b_left );
	one.addKeyEvent( SDLK_d, b_right );
	one.addKeyEvent( SDLK_s, b_down );*/

	// Set the scene in the engine
	engine.setScene(&one);
	
	// Get the engine running.
	engine.run();

	return 0;
}

#include "Engine.hpp"
#include "HUD.hpp"
#include <SDL_ttf.h>
#include "Player.hpp"
#include "LifeBar.hpp"
#include <string>

// call sprite constructor with only sorting layer 
// so we can take care of our own surface
HUD::HUD(Player* inputPlayer) : Sprite(0){
	stick = TTF_OpenFont("../assets/stick.ttf", 48);
	if(stick == NULL){
		SDL_Log("No font. %s", TTF_GetError());
	}
	color.r=0;
	color.g=0;
	color.b=0;
	surface = TTF_RenderText_Solid(stick, "Score: 0", color); 
	if(surface == NULL){
		SDL_Log("Can't create text. %s", SDL_GetError());
	}
	texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), surface);
	if(texture == NULL){
		SDL_Log("Can't create texture. %s", SDL_GetError());
	}
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;



	currentPlayer = inputPlayer;
}

HUD::~HUD(){
	
}

void HUD::update(double delta){
	// update HUD text with the current score from the player
	int score = currentPlayer->getScore();
	std::string scoreString = "Score: " + std::to_string(score);

	surface = TTF_RenderText_Solid(stick, scoreString.c_str(), color); 
	texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), surface);
}


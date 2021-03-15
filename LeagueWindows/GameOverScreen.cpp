#include "Sprite.hpp"
#include "Utility.hpp"
#include "Engine.hpp"
#include <SDL.h>
#include "GameOverScreen.hpp"

// We made this one ourselves :)
GameOverScreen::GameOverScreen() : Sprite("../assets/GameOver.jpg", 0) {

}

GameOverScreen::~GameOverScreen() {

}

void GameOverScreen::update(double delta) {

}

void GameOverScreen::draw() {
	SDL_Rect* dst = new SDL_Rect();
	dst->x = position.getX();
	dst->y = position.getY();
	dst->w = rect->w * 1.28;
	dst->h = rect->h * 1.231;
	SDL_RenderCopy(Engine::getRenderer(), texture, NULL, dst);
}
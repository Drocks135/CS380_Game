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
	SDL_Rect dst;
	dst.x = position.getX();
	dst.y = position.getY();
	dst.w = rect->w * 0.52;
	dst.h = rect->h * 0.65;
	SDL_RenderCopy(Engine::getRenderer(), texture, NULL, &dst);
}
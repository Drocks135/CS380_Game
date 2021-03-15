#include "Sprite.hpp"
#include "Utility.hpp"
#include "Engine.hpp"
#include <SDL.h>
#include "Background.hpp"

// Background sprite is open-source (no licensing available) from https://jestan.itch.io/classic-rpg
// In a comment, the creator specifies that the asset is free to use.
Background::Background() : Sprite("../assets/Background.jpg", 0){

}

Background::~Background() {

}

void Background::update(double delta) {
	
}

void Background::draw() {
	SDL_Rect dst;
	dst.x = position.getX();
	dst.y = position.getY();
	dst.w = rect->w * 1.28;
	dst.h = rect->h * 1.231;
	SDL_RenderCopy(Engine::getRenderer(), texture, NULL, &dst);
}

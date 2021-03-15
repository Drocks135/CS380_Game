#include "Engine.hpp"
#include "Sprite.hpp"
#include <string>
#include <SDL.h>

// constructor mainly for HUD, where there is no path
// and the surface is taken care of in the constructor
Sprite::Sprite(int sortingLayer) {
	layer = sortingLayer;
}

Sprite::Sprite(std::string path, int sortingLayer) {
	layer = sortingLayer;

	surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		SDL_Log("Unable to load sprite.");
		exit(1);
	}
	texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), surface);
	if (texture == NULL) {
		SDL_Log("-----> HAVE YOU CREATED THE ENGINE YET? <-----");
		SDL_Log("Unable to create texture. %s", SDL_GetError());
	}
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
}

Sprite::Sprite(SDL_Surface* ptrSurface, int sortingLayer) {
	layer = sortingLayer;

	surface = ptrSurface;
	if (surface == NULL) {
		SDL_Log("Unable to load sprite.");
		exit(1);
	}
	texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), surface);
	if (texture == NULL) {
		SDL_Log("-----> HAVE YOU CREATED THE ENGINE YET? <-----");
		SDL_Log("Unable to create texture. %s", SDL_GetError());
	}
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void Sprite::draw() {
	SDL_Rect dst;
	dst.x = position.getX();
	dst.y = position.getY();
	dst.w = rect->w;
	dst.h = rect->h;
	SDL_RenderCopy(Engine::getRenderer(), texture, NULL, &dst);
}

void Sprite::setLayer(int sortingLayer) {
	if (sortingLayer < 0) {
		SDL_Log("Sorting layer cannot be negative");
	}
	else {
		layer = sortingLayer;
	}
}

int Sprite::getLayer() {
	return layer;
}

int Sprite::getX() {
	return rect->x;
}

int Sprite::getY() {
	return rect->y;
}

int Sprite::getWidth() {
	return rect->w;
}

int Sprite::getHeight() {
	return rect->h;
}

// Comparator based on sorting layer
bool Sprite::operator<(const Sprite& other) {
	return (this->layer < other.layer);
}
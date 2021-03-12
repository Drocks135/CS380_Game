#ifndef			__HPP__SPRITE__
#define			__HPP__SPRITE__

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Interfaces.hpp"
#include "Utility.hpp"

class Sprite : public DUGameObject {
public:
	Sprite(std::string path, int sortingLayer);
	Sprite(SDL_Surface* ptrSurface, int sortingLayer);
	virtual ~Sprite();

	void draw();
	void setLayer(int sortingLayer);
	int getLayer();
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	bool operator<(const Sprite& other);
protected:
	Vector3 velocity;
	int actionState;
	int layer;

};

#endif

#ifndef			__HPP__SPRITE__
#define			__HPP__SPRITE__

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Interfaces.hpp"
#include "Utility.hpp"

class Sprite : public DUGameObject {
public:
	Sprite(int sortingLayer);
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

	// overloads the < operator to compare sorting layer
	bool operator<(const Sprite& other);
protected:
	Vector3 velocity;
	int layer;

};

#endif

#ifndef			__HPP__BANANA__
#define			__HPP__BANANA__

#include "Sprite.hpp"
#include "Utility.hpp"
#include <SDL.h>

class Banana : public Sprite {
	public:
		Banana();
		Banana(SDL_Surface* inputSurface);
		~Banana();
		void update(double delta);
		void left(double delta);
		void right(double delta);
		void up(double delta);
		void down(double delta);
};

#endif

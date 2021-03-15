#ifndef			__HPP__BACKGROUND__
#define			__HPP__BACKGROUND__

#include "Sprite.hpp"
#include "Utility.hpp"
#include "Engine.hpp"
#include <SDL.h>

// The background sprite for the game
class Background : public Sprite {
public:
	Background();
	~Background();
	void update(double delta);
	void draw();
};

#endif
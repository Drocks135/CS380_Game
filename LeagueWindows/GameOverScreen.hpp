#ifndef			__HPP__GAMEOVER__
#define			__HPP__GAMEOVER__

#include "Sprite.hpp"
#include "Utility.hpp"
#include "Engine.hpp"
#include <SDL.h>

// The game over sprite for the game
class GameOverScreen : public Sprite {
public:
	GameOverScreen();
	~GameOverScreen();
	void update(double delta);
	void draw();
};

#endif

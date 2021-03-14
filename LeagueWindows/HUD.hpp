#ifndef			__HPP__HUD__
#define			__HPP__HUD__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Interfaces.hpp"
#include "Utility.hpp"
#include "Player.hpp"
#include "Sprite.hpp"
#include <string>

class HUD : public Sprite {
	public:
		HUD(Player* inputPlayer);
		~HUD();
		void update(double delta);	
	private:
		Player* currentPlayer;
		TTF_Font* stick;
		SDL_Color color;
};

#endif

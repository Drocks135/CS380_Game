#ifndef			__HPP__HUD__
#define			__HPP__HUD__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Interfaces.hpp"
#include "Utility.hpp"
#include "Player.hpp"
#include <string>

class HUD : public DUGameObject {
	public:
		HUD(Player* inputPlayer);
		~HUD();
		void update(double delta);
		void draw();	
	private:
		Player* currentPlayer;
		TTF_Font* stick;
		SDL_Color color;

};

#endif

#ifndef __HPP__Collision
#define __HPP__Collision

#include "Sprite.hpp"
#include "Enemy.hpp"
#include <vector>

class Collision : DUGameObject{
	public:
		Collision();
		bool didCollide(Sprite &firstSprite, Sprite &secondSprite);
		bool didCollide(Enemy &e, SDL_Rect &swordHitbox);
		static bool didCollide(int startAX, int startAY, int widthA, int heightA, int startBX, int startBY, int widthB, int heightB);
		private:
		std::vector<Sprite> collidableObjects;
};
#endif


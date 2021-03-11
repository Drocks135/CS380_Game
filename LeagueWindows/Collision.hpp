#ifndef __HPP__Collision
#define __HPP__Collision

#include "Sprite.hpp"
#include <vector>

class Collision : DUGameObject{
	public:
		Collision();
		bool didCollide(Sprite &firstSprite, Sprite &secondSprite);
		private:
		std::vector<Sprite> collidableObjects;
};
#endif


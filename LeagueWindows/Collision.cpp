#include "Collision.hpp"
#include "Sprite.hpp"



Collision::Collision()
{

}

bool Collision::didCollide(Sprite& firstSprite, Sprite& secondSprite)
{
	firstSprite;
	return false;
}

bool Collision::didCollide(Enemy& e, SDL_Rect& swordHitbox)
{
	
	return false;
}

bool Collision::didCollide(int startAX, int startAY, int widthA, int heightA, int startBX, int startBY, int widthB, int heightB)
{
	//check each rectangle edge
	if ((startAX < startBX + widthB && startAX + widthA > startBX) &&
		startAY < startBY + heightB && startAY + heightA > startBY) {
		return true;
	}
	return false;
}





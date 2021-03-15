#ifndef			__HPP__LifeBar__
#define			__HPP__LifeBar__

#include "AnimatedSprite.hpp"
#include "Utility.hpp"
#include "Player.hpp"
#include <SDL.h>

class LifeBar : public AnimatedSprite {
public:
	LifeBar(Player* player);
	~LifeBar();
	void update(double delta);
	void setLife();
private:
	Player* player;
	void loadAnimData(AnimData& HealthAnimationData);
};


#endif
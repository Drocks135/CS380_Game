#ifndef			__HPP__LifeBar__
#define			__HPP__LifeBar__

#include "AnimatedSprite.hpp"
#include "Utility.hpp"
#include <SDL.h>

class LifeBar : public AnimatedSprite {
public:
	LifeBar();
	~LifeBar();
	void update(double delta);
	void setLife();
	void down(double delta, bool start);
	void up(double delta, bool start);
};

#endif
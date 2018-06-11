#include "explosion.h"



explosion::explosion():radius(0),Location(0,0)
{
}


explosion::explosion(double radius, const _2D& Location):radius(radius),Location(Location) 
{
}

explosion::~explosion()
{
}

void explosion::tick() {
	radius -= EXPLOTION_CONVERGE_SPEED;
}

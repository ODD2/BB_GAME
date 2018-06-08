#include "vessel.h"
#include "missile.h"


vessel::vessel()
{
}

vessel::~vessel()
{
}


bool vessel::hit(missile& missile_obj) {
	if (Distance_2D(Location, missile_obj.Location) < 1.5) {
		HP -= missile_obj.damage;
		return HP < 0;
	}
	return false;
}

void vessel::tick() {
	//move tick
	if (!speed);
	else if (Location.x >= MAP_INTERVALS || Location.y >= MAP_INTERVALS || Location.x <= 0 || Location.y <= 0) {
		speed = 0;
	}
	else {
		double r = speed / (1000.0 / UPDATE_PER_MS * 4 );
		double radial = (angle/180*_PI_);
		Location.x += r * cos(radial);
		Location.y -= r * sin(radial);

		if (Location.x < 0) Location.x = 0;
		else if (Location.x > MAP_INTERVALS) Location.x = MAP_INTERVALS;
		if (Location.y < 0) Location.y = 0;
		else if (Location.y > MAP_INTERVALS) Location.y = MAP_INTERVALS;
	}
	if (atkCD) {
		atkCD -= (double)PER_SECOND_IN_GAME * UPDATE_PER_MS / 1000;
		//if (atkCD < 0) atkCD = 0;
	}
	if (defCD) {
		defCD -= (double)PER_SECOND_IN_GAME * UPDATE_PER_MS / 1000;
		//if (defCD < 0) defCD = 0;
	}
}

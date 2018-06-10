#include "vessel.h"
#include "missile.h"


vessel::vessel()
{
}

vessel::vessel(string name) {
	this->name = name;
}

vessel::vessel(string name,const _2D& Location) {
	this->name = name;
	this->Location = Location;
}

vessel::~vessel()
{
}

bool vessel::hit(missile& missile_obj) {
	if (Distance_2D(Location, missile_obj.Destination.to_2D()) <= 1.5) {
		HP -= missile_obj.damage;
		return true;
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
		double r = speed / (60.0 / PER_SECOND_IN_GAME ) /(1000.0 / UPDATE_PER_MS  );
		double radial = (angle/180*_PI_);
		Location.x += r * cos(radial);
		Location.y -= r * sin(radial);

		if (Location.x < 0) Location.x = 0;
		else if (Location.x > MAP_INTERVALS) Location.x = MAP_INTERVALS;
		if (Location.y < 0) Location.y = 0;
		else if (Location.y > MAP_INTERVALS) Location.y = MAP_INTERVALS;
	}

	//cool down tick
	if (atkCD) {
		atkCD -= PER_SECOND_IN_GAME * UPDATE_PER_MS / 1000;
		if (atkCD < 0) atkCD = 0;
	}
	if (defCD) {
		defCD -= PER_SECOND_IN_GAME * UPDATE_PER_MS / 1000;
		if (defCD < 0) defCD = 0;
	}
}

#include "missile.h"




missile::missile()
{
}

missile::~missile()
{
}


//Constructure without error detection on any variables;
//Besure that these arguments are 100% correct;
missile::missile(const _2D& Loc, const _2D& Des, const double& speed,const double& damage) {
	this->speed = speed;
	this->damage = damage;
	Location = Loc;
	Destination = Des;
	angle = atan2(Des.y - Loc.y, Des.x - Loc.x);
}

bool missile::move() {
	double r = speed / (1000.0 / UPDATE_PER_MS * 4);
	double radial = angle/180 * _PI_;
	Location.x += r * cos(radial);
	Location.y -= r * sin(radial);

	if (OutOfRange_2D(Location)) {
		return land();
	}
	else return true;
}

bool missile::land() {
	if (Location == Destination) {
		return true;
	}
	return false;
}

void missile::setAngle() {
	angle = atan2(Destination.y - Location.y, Destination.x - Location.x);
}
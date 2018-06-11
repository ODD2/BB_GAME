#include "missile.h"




missile::missile()
{
}

missile::~missile()
{
}

//Constructure without error detection on any variables;
//Besure that these arguments are 100% correct;
missile::missile(const _3D& Loc, const _3D& Des, const double& speed,const double& damage) {
	this->speed = speed;
	this->damage = damage;
	Location = Loc;
	Destination = Des;
	angle = -1 * atan2(Des.y - Loc.y, Des.x - Loc.x) * 180 / _PI_;
}

bool missile::tick() {
	double r = speed / (60.0 / PER_SECOND_IN_GAME) / (1000.0 / UPDATE_PER_MS);
	double radial = angle/180 * _PI_;
	Location.x += r * cos(radial);
	Location.y -= r * sin(radial);

	if (OutOfRange_3D(Location)) {
		return false;
	}
	else return true;
}

bool missile::land() {
	if (Location.to_2D() == Destination.to_2D()) {
		Location = Destination;
		Location.z = 0;
		return true;
	}
	return false;
}

inline void missile::setAngle() {
	angle = -1 * atan2(Destination.y - Location.y, Destination.x - Location.x)*180 / _PI_;
}
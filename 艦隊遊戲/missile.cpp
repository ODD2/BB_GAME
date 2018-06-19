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
	realSpeed= speed / (60.0 / PER_SECOND_IN_GAME) / (1000.0 / UPDATE_PER_MS);
	angle = -1 * atan2(Des.y - Loc.y, Des.x - Loc.x) * 180 / _PI_;
}

missile::missile(const _3D& Loc, const double& speed, const double& damage):
	Location(Loc),speed(speed),damage(damage)
{
}

bool missile::tick() {

	double radial = angle/180 * _PI_;
	Location.x += realSpeed * cos(radial);
	Location.y -= realSpeed * sin(radial);

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

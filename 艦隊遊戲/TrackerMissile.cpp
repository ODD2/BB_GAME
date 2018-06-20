#include "TrackerMissile.h"



TrackerMissile::TrackerMissile()
{
}

TrackerMissile::TrackerMissile(const _3D& loc, vessel * target, const double& speed, const double& damage):
	missile(loc, target->Location, speed, damage),target(target)
{

}

TrackerMissile::~TrackerMissile()
{
}

bool TrackerMissile::tick() {

	if (target == nullptr) {
	}
	else if (target->HP <= 0) {
		target = nullptr;
	}
	else {
		Destination.x = target->Location.x;
		Destination.y = target->Location.y;
	}

	angle = Angle_2D(Location.to_2D(), Destination.to_2D());
	double radial = angle / 180 * _PI_;
	Location.x += realSpeed * cos(radial);
	Location.y -= realSpeed * sin(radial);
	

	if (OutOfRange_3D(Location)) {
		return false;
	}
	else return true;
}

bool TrackerMissile::land() {
	if (Location.to_2D() == Destination.to_2D()) {
		Location = Destination;
		Location.z = 0;
		return true;
	}
	return false;
}
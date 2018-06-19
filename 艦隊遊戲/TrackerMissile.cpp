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
	if (target == nullptr|| target->HP <= 0) {
		return false;
	}

	Angle_2D(Location.to_2D(), target->Location);
	double radial = angle / 180 * _PI_;
	Location.x += realSpeed * cos(radial);
	Location.y -= realSpeed * sin(radial);

	if (OutOfRange_3D(Location)) {
		return false;
	}
	else return true;
}

bool TrackerMissile::land() {
	if (Location.to_2D() == target->Location) {
		Location = target->Location;
		Location.z = 0;
		return true;
	}
	return false;
}
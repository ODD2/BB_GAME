#include "DD.h"
#include "missile.h"


DD::DD()
{
}


DD::~DD()
{
}




bool DD::defense(missile& missile_obj) {
	if (!defCD) {
		defCD = DD_DEFENSE_CD;
		if (Distance_2D(this->Location, missile_obj.Location) < DD_DEFENSE_RANGE) {

			return true;
		}
	}
	return false;
}

missile DD::attack(_2D& atk_Destination)throw(int) {
	if (OutOfRange_2D(atk_Destination)) {
		throw - 1;
	}
	else {
		return missile(Location, atk_Destination, DD_MISSILE_SPEED, DD_MISSILE_DAMAGE);
	}
}

bool DD::move(double angle, double speed) {
	if (fabs(speed)> DD_MAX_SPEED) {
		return false;
	}
	this->speed = speed;
	this->angle = fmod(angle, 360);
	return true;
}
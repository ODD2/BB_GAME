#include "BB.h"
#include "missile.h"


BB::BB()
{
}


BB::~BB()
{
}




bool BB::defense(missile& missile_obj) {
	if (!defCD) {
		defCD = BB_DEFENSE_CD;
		if (Distance_2D(this->Location, missile_obj.Location) < BB_DEFENSE_RANGE) {

			return true;
		}
	}
	return false;
}

missile BB::attack(_2D& atk_Destination)throw(int) {
	if (OutOfRange_2D(atk_Destination)) {
		throw - 1;
	}
	else {
		return missile(Location, atk_Destination, BB_MISSILE_SPEED, BB_MISSILE_DAMAGE);
	}
}

bool BB::move(double angle, double speed) {
	if ( fabs(speed )> BB_MAX_SPEED) {
		return false;
	}
	this->speed = speed;
	this->angle = fmod(angle, 360);
	return true;
}
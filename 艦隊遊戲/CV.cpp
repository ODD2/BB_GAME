#include "CV.h"
#include "missile.h"


CV::CV()
{
}


CV::~CV()
{
}



bool CV::defense(missile& missile_obj) {
	if (!defCD) {
		defCD = CV_DEFENSE_CD;
		if (Distance_2D(this->Location, missile_obj.Location.to_2D()) < CV_DEFENSE_RANGE) {

			return true;
		}
	}
	return false;
}

missile CV::attack(_2D& atk_Destination)throw(int) {
	if (OutOfRange_2D(atk_Destination)) {
		throw - 1;
	}
	else {
		return missile(Location, atk_Destination, CV_MISSILE_SPEED, CV_MISSILE_DAMAGE);
	}
}

bool CV::move(double angle, double speed) {
	if (fabs(speed)> CV_MAX_SPEED) {
		return false;
	}
	this->speed = speed;
	this->angle = fmod(angle, 360);
	return true;
}
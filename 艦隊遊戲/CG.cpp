#include "CG.h"
#include "missile.h"


CG::CG()
{
}


CG::~CG()
{
}



bool CG::defense(missile& missile_obj) {
	if (!defCD) {
		defCD = CG_DEFENSE_CD;
		if (Distance_2D(this->Location, missile_obj.Location.to_2D()) < CG_DEFENSE_RANGE) {

			return true;
		}
	}
	return false;
}

missile CG::attack(_2D& atk_Destination)throw(int) {
	if (OutOfRange_2D(atk_Destination)) {
		throw - 1;
	}
	else {
		return missile(Location, atk_Destination, CG_MISSILE_SPEED, CG_MISSILE_DAMAGE);
	}
}

bool CG::move(double angle, double speed) {
	if (fabs(speed)> CG_MAX_SPEED) {
		return false;
	}
	this->speed = speed;
	this->angle = fmod(angle, 360);
	return true;
}
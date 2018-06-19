#include "DD.h"
#include "missile.h"


DD::DD()
{
	HP = DD_HP;
}

DD::~DD()
{
}

DD::DD(string  name):vessel(name)
{
	HP = DD_HP;
}

DD::DD(string name, const _2D& Location) : vessel(name, Location)
{
	HP = DD_HP;
}

bool DD::defense(missile& missile_obj) {
	if (!defCD) {
		defCD = DD_DEFENSE_CD;
		if (Distance_2D(this->Location, missile_obj.Location.to_2D()) < DD_DEFENSE_RANGE) {
			return true;
		}
	}
	return false;
}

missile DD::attack(_2D& atk_Destination)throw(int) {
	if (OutOfRange_2D(atk_Destination)) {
		throw - 1;
	}
	else if (atkCD > 0) {
		throw - 2;
	}
	else {
		atkCD = DD_ATTACK_CD;
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
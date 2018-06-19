#include "BB.h"
#include "missile.h"


BB::BB()
{
	HP = BB_HP;
	name = "unknown";
}

BB::BB(string  name):vessel(name) {
	HP = BB_HP;
}

BB::BB(string name, const _2D& Location) : vessel(name, Location)
{
	HP = BB_HP;
}

BB::~BB()
{
}

bool BB::defense(missile& missile_obj) {
	if (!defCD) {
		defCD = BB_DEFENSE_CD;
		if (Distance_2D(this->Location, missile_obj.Location.to_2D()) < BB_DEFENSE_RANGE) {
			return true;
		}
	}
	return false;
}

missile* BB::attack(_2D& atk_Destination)throw(int) {
	if (OutOfRange_2D(atk_Destination)) {
		throw -1;
	}
	else if (atkCD >= 0) {
		throw -2;
	}
	else {
		atkCD = BB_ATTACK_CD;
		return new missile(Location, atk_Destination, BB_MISSILE_SPEED, BB_MISSILE_DAMAGE);
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
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

bool DD::defense(string mode, ...) {
	if (!defCD) {
		if (mode == DD_DEF_MODE_1) {
			va_list vl;
			va_start(vl, mode);
			missile& missile_obj = va_arg(vl, missile);
			va_end(vl);

			defCD = DD_DEFENSE_CD;
			if (Distance_2D(this->Location, missile_obj.Location.to_2D()) <= DD_DEFENSE_RANGE) {
				return true;
			}

			return false;
			
		}
		else {
			throw - 2;
		}
	}
	return false;
}

missile* DD::attack(string mode, ...)throw(int)
{
	if (atkCD)
	{
		throw - 2;
	}
	else if (mode == DD_ATK_MODE_1) {
		va_list vl;
		va_start(vl, mode);


		_2D& atk_Destination = va_arg(vl, _2D);
		if (OutOfRange_2D(atk_Destination)) {
			throw - 1;
		}
		else {
			atkCD = DD_ATTACK_CD;
			return new missile(Location, atk_Destination, DD_MISSILE_SPEED, DD_MISSILE_DAMAGE);
		}


		va_end(vl);
	}
	else {
		throw - 3;
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
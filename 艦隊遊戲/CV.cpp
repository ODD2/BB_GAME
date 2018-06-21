#include "CV.h"
#include "missile.h"


CV::CV()
{
	HP = CV_HP;
}

CV::~CV()
{
}

CV::CV(string  name):vessel(name) {
	HP = CV_HP;
}

CV::CV(string name, const _2D& Location) : vessel(name, Location)
{
	HP = CV_HP;
}

bool CV::defense(string mode, ...) {
	if (!defCD) {
		if (mode == CV_DEF_MODE_1) {
			va_list vl;
			va_start(vl, mode);
			missile& missile_obj = va_arg(vl, missile);
			va_end(vl);

			defCD = CV_DEFENSE_CD;
			if (Distance_2D(this->Location, missile_obj.Location.to_2D()) <= CV_DEFENSE_RANGE) {
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

missile* CV::attack(string mode, ...)throw(int)
{
	if (atkCD)
	{
		throw - 2;
	}
	else if (mode == CV_ATK_MODE_1) {
		va_list vl;
		va_start(vl, mode);
		atkCD = CV_ATTACK_CD;

		_2D& atk_Destination = va_arg(vl, _2D);
		if (OutOfRange_2D(atk_Destination)||Distance_2D(Location, atk_Destination)>CV_ATTACK_RANGE) {
			throw atk_Destination;
		}
		else {
			return new missile(Location, atk_Destination, CV_MISSILE_SPEED, CV_MISSILE_DAMAGE);
		}


		va_end(vl);
	}
	else {
		throw - 3;
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
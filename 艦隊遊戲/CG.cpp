#include "CG.h"
#include "missile.h"


CG::CG()
{
	HP = CG_HP;
}

CG::~CG()
{
}

CG::CG(string  name) {
	this->name = name;
	HP = CG_HP;
}

CG::CG(string name, const _2D& Location) : vessel(name, Location)
{
	HP = CG_HP;
}

bool CG::defense(string mode, ...) {
	if (!defCD) {
		if (mode == CG_DEF_MODE_1) {
			va_list vl;
			va_start(vl, mode);
			missile& missile_obj = va_arg(vl, missile);
			va_end(vl);
			defCD = CG_DEFENSE_CD;

			if (Distance_2D(this->Location, missile_obj.Location.to_2D()) <= CG_DEFENSE_RANGE) {
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

missile* CG::attack(string mode, ...)throw(int)
{
	if (atkCD)
	{
		throw - 2;
	}
	else if (mode == CG_ATK_MODE_1 ) {
		va_list vl;
		va_start(vl, mode);
		atkCD = CG_ATTACK_CD;

		_2D& atk_Destination = va_arg(vl, _2D);
		if (OutOfRange_2D(atk_Destination) || Distance_2D(Location, atk_Destination)>CG_ATTACK_RANGE) {
			throw atk_Destination;
		}
		else {

			return new missile(Location, atk_Destination, CG_MISSILE_SPEED, CG_MISSILE_DAMAGE);
		}


		va_end(vl);
	}
	else {
		throw - 3;
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
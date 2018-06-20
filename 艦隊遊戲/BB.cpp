#include "BB.h"
#include "missile.h"
#include "TrackerMissile.h"


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

bool BB::defense(string mode, ...) {
	if (!defCD) {
		if (mode == BB_DEF_MODE_1) {
			va_list vl;
			va_start(vl, mode);
			missile& missile_obj = va_arg(vl, missile);
			va_end(vl);

			defCD = BB_DEFENSE_CD;

			if (Distance_2D(this->Location, missile_obj.Location.to_2D()) <= BB_DEFENSE_RANGE) {
				return true;
			}

			return false;

			
		}
		else if (mode == BB_DEF_MODE_2) {
			defCD = BB_DEFENSE_CD;
			return true;
		}
		else {
			throw - 2;
		}
	}
	return false;
}

missile* BB::attack(string mode, ...)throw(int) 
{
	if (atkCD)
	{
		throw -2;
	}
	else if(mode == BB_ATK_MODE_1){
		va_list vl;
		va_start(vl, mode);


		_2D& atk_Destination = va_arg(vl, _2D);
		if (OutOfRange_2D(atk_Destination)) {
			throw -1;
		}
		else {
			atkCD = BB_ATTACK_CD;
			return new missile(Location, atk_Destination, BB_MISSILE_SPEED, BB_MISSILE_DAMAGE);
		}


		va_end(vl);
	}
	else if (mode == BB_ATK_MODE_2) {
		va_list vl;
		va_start(vl, mode);

		atkCD = BB_ATTACK_CD;
		vessel * target = va_arg(vl, vessel*);
		return new TrackerMissile(Location,target , BB_MISSILE_SPEED, BB_MISSILE_DAMAGE);



		va_end(vl);
	}
	else {
		throw -3;
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
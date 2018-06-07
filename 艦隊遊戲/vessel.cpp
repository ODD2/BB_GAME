#include "vessel.h"



vessel::vessel()
{
}


vessel::~vessel()
{
}

bool vessel::setDes(_2D& des) {
	if (des.x > MAP_INTERVALS || des.y > MAP_INTERVALS || des.x < 0 || des.y < 0) {
		return false;
	}

	Destination = des;

	return true;
}
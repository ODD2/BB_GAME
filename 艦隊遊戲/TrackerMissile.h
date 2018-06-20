#pragma once
#include "missile.h"
#include "vessel.h"
class TrackerMissile :
	public missile
{
public:
	TrackerMissile();
	TrackerMissile(const _3D&,vessel * target, const double&, const double&);//location, target,speed, damage.
	~TrackerMissile();
	virtual bool tick();
	virtual bool land();
protected:
	vessel * target;
	//ResourceClass
	virtual unsigned int PicSerial() { return PICS::PIC_ATK_TRACKER; };
};


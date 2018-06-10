#pragma once
#include <math.h>
#include "location_system.h"
#include "GLOBALSETTINGS.h"

class missile
{
	friend class vessel;
	friend class BB;
	friend class CG;
	friend class CV;
	friend class DD;
	friend class MainForm;



public:
	missile();

	//Location, Destination, Speed, Damage
	missile(const _3D&, const _3D&,const double&,const double&);
	virtual ~missile();
	virtual bool move();
	virtual bool land();

protected:
	_3D Location = {0,0,0};
	_3D Destination = {-1,-1,-1};
	double angle = 0;
	double speed = 0;
	double damage = 0;

	inline void setAngle();
};


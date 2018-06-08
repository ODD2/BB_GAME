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
	missile(const _2D&, const _2D&,const double&,const double&);
	virtual ~missile();
	virtual bool move();
	virtual bool land();

protected:
	_2D Location = {0,0};
	_2D Destination = {-1,-1};
	double angle = 0;
	double speed = 0;
	double damage = 0;

	inline void setAngle();
};


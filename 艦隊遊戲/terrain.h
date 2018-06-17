#pragma once
#include <string>
#include "vessel.h"
#include "location_system.h"
#include "missile.h"
#include "ResourceClass.h"

class terrain :public ResourceClass
{
public:
	terrain(string,const _2D&, const _2D&,double);
	virtual ~terrain();


	virtual bool tick() = 0;
	virtual bool VesselCollision(vessel&)=0;
	virtual bool MissileCollision(missile&)=0;


protected:
	_2D Location_LU;
	_2D Location_RD;
	double height;
	string name;
};


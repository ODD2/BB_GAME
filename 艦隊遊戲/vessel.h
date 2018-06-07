#pragma once
#include <iostream>
#include <string>
#include "GLOBALSETTINGS.h"
#include "location_system.h"
using namespace std;

class missile;

class vessel
{
public:
	vessel();
	virtual ~vessel();
	bool setDes(_2D&);

	virtual void move()=0;
	virtual bool hit(missile&)=0;
	virtual bool defense(missile&)=0;
	virtual missile attack(_2D&)=0;
protected:
	virtual missile missileCreate()=0;
	_2D Location;
	_2D Destination;
	double atkCD=0;
	double defCD=0;
};


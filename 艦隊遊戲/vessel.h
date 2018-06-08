#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "GLOBALSETTINGS.h"
#include "location_system.h"
using namespace std;

class missile;

class vessel
{
	friend class MainForm;
public:
	vessel();
	virtual ~vessel();

	
	virtual bool hit(missile&);
	virtual bool defense(missile&)=0;
	virtual missile attack(_2D&)throw(int) =0;
	virtual bool move(double, double) = 0;
	
	virtual void tick();


protected:
	//about position & movement
	_2D Location = {0.1,0.1};
	double angle = 0;
	double speed = 0;

	//about cool downs
	double atkCD=15;
	double defCD=30;

	//about HP
	double HP = 0;
};


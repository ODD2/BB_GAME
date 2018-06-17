#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "GLOBALSETTINGS.h"
#include "location_system.h"
#include "ResourceClass.h"
using namespace std;

class missile;

class vessel:public ResourceClass
{
	friend class MainForm;
	friend class BattleField;
public:
	vessel();
	vessel(string);
	vessel(string, const _2D&);
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
	double atkCD=0;
	double defCD=0;

	//about HP
	double HP = 0;

	//about name
	string name;
};


#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <stdarg.h>
#include "GLOBALSETTINGS.h"
#include "location_system.h"
#include "ResourceClass.h"

using namespace std;

class missile;

class vessel:public ResourceClass
{
	friend class MainForm;
	friend class BattleField;

	//MISSILES
	friend class TrackerMissile;
public:
	vessel();
	vessel(string);
	vessel(string, const _2D&);
	virtual ~vessel();

	//action
	virtual bool hit(missile&);
	virtual bool defense(string,...)=0;//mode, va_list
	virtual missile* attack(string,...)throw(int) =0; //mode ,va_list
	virtual bool move(double, double) = 0;
	
	virtual void tick();


	//explanations
	virtual string attackHELP() {
		return "attack.";
	}
	virtual string defenseHELP() {
		return  "defense.";
	}
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


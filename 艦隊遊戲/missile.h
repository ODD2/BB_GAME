#pragma once
#include <math.h>
#include <string>
#include "location_system.h"
#include "GLOBALSETTINGS.h"
#include "ResourceClass.h"
using namespace std;
#define MISSILE_RADIUS 1.5

class missile:public ResourceClass
{
	friend class vessel;
	friend class BB;
	friend class CG;
	friend class CV;
	friend class DD;
	friend class MainForm;
	friend class BattleField;


public:
	missile();

	//Location, Destination, Speed, Damage
	missile(const _3D&, const _3D&,const double&,const double&);
	virtual ~missile();
	virtual bool tick();
	virtual bool land();

protected:
	_3D Location = {0,0,0};
	_3D Destination = {-1,-1,-1};
	double angle = 0;
	double speed = 0;
	double damage = 0;
	double damageRadius = MISSILE_RADIUS;
	string name="";


	inline void setAngle();

	//ResourceClass
	virtual unsigned int PicSerial() { return PICS::PIC_MS; };
};


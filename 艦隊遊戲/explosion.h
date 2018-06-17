#pragma once
#define EXPLOTION_CONVERGE_SPEED 0.05
#include "location_system.h"
#include "ResourceClass.h"

class explosion:public ResourceClass
{
	friend class MainForm;
	friend class BattleField;
public:
	explosion();
	explosion(double, const _2D&);//damage , Location
	~explosion();

	void tick();
protected:
	double radius = 0;
	_2D Location = {0,0};


	//ResourceClass
	virtual unsigned int PicSerial() { return PICS::PIC_EX; };
};


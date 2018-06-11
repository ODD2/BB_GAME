#pragma once
#define EXPLOTION_CONVERGE_SPEED 0.01
#include "location_system.h"

class explosion
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
};


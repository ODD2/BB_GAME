#pragma once
#include "vessel.h"
#define DD_MAX_SPEED 3
#define DD_MISSILE_SPEED 3
#define DD_MISSILE_DAMAGE 1
#define DD_DEFENSE_RANGE 20
#define DD_ATTACK_RANGE 10
#define DD_DEFENSE_CD 60
#define DD_ATTACK_CD 15
#define DD_HP 2 

class DD :
	public vessel
{
public:
	DD();
	virtual ~DD();

	virtual bool defense(missile&);
	virtual missile attack(_2D&)throw(int);
	virtual bool move(double, double);
protected:
};


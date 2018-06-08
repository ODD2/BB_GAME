#pragma once
#include "vessel.h"
#define CG_MAX_SPEED 2
#define CG_MISSILE_SPEED 3
#define CG_MISSILE_DAMAGE 2
#define CG_DEFENSE_RANGE 15
#define CG_ATTACK_RANGE 15
#define CG_DEFENSE_CD 30
#define CG_ATTACK_CD 30
#define CG_HP 3

class CG :
	public vessel
{
public:
	CG();
	virtual ~CG();

	virtual bool defense(missile&);
	virtual missile attack(_2D&)throw(int);
	virtual bool move(double, double);
protected:
};


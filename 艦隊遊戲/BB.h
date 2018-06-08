#pragma once
#include "vessel.h"
//#define BB_MAX_SPEED 1
#define BB_MAX_SPEED 20
#define BB_MISSILE_SPEED 2
#define BB_MISSILE_DAMAGE 3
#define BB_DEFENSE_RANGE 10
#define BB_ATTACK_RANGE 20
#define BB_DEFENSE_CD 30
#define BB_ATTACK_CD 30
#define BB_HP 4 

class BB :
	public vessel
{
public:
	BB();
	virtual ~BB();

	virtual bool defense(missile&);
	virtual missile attack(_2D&)throw(int) ;
	virtual bool move(double, double);
protected:
};


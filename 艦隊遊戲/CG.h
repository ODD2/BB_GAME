#pragma once
#include "vessel.h"
#include "GLOBALCOMMAD.h"
//Attributes
#define CG_MAX_SPEED 2
#define CG_MISSILE_SPEED 3
#define CG_MISSILE_DAMAGE 2
#define CG_DEFENSE_RANGE 15
#define CG_ATTACK_RANGE 15
#define CG_DEFENSE_CD 30
#define CG_ATTACK_CD 30
#define CG_HP 3


//Attack Definitions
#define CG_ATTACK_MODES 1
#define CG_ATK_MODE_1 ATTACK_MISSILE


//Defense Definitions
#define CG_DEFENSE_MODES 1
#define CG_DEF_MODE_1 DEFENSE_LAZER
class CG :
	public vessel
{
public:
	CG();
	CG(string);
	CG(string, const _2D&);
	virtual ~CG();

	virtual bool defense(string, ...);//mode, va_list
	virtual missile* attack(string, ...)throw(int); //mode ,va_list
	virtual bool move(double, double);
protected:
	//ResourceClass
	virtual unsigned int PicSerial() { return PICS::PIC_CG; };
};


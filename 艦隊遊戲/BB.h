#pragma once
#include "vessel.h"
#include "GLOBALCOMMAD.h"
//Attributes
#define BB_MAX_SPEED 1
#define BB_MISSILE_SPEED 2
#define BB_MISSILE_DAMAGE 3
#define BB_DEFENSE_RANGE 10
#define BB_ATTACK_RANGE 20
#define BB_DEFENSE_CD 30
#define BB_ATTACK_CD 30
#define BB_HP 4 


//Attack Definitions
#define BB_ATTACK_MODES 2
#define BB_ATK_MODE_1 ATTACK_MISSILE
#define BB_ATK_MODE_2 ATTACK_TRACKER


//Defense Definitions
#define BB_DEFENSE_MODES 1
#define BB_DEF_MODE_1 DEFENSE_LAZER
#define BB_DEF_MODE_2 DEFENSE_NOVA

class BB :
	public vessel
{
public:
	BB();
	BB(string);
	BB(string, const _2D&);
	virtual ~BB();

	virtual bool defense(string, ...);//mode, va_list
	virtual missile* attack(string, ...)throw(int); //mode ,va_list
	virtual bool move(double, double);
protected:

	//ResourceClass
	virtual unsigned int PicSerial() { return PICS::PIC_BB; };
};


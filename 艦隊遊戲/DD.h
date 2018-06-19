#pragma once
#include "vessel.h"
//Attributes
#define DD_MAX_SPEED 3
#define DD_MISSILE_SPEED 3
#define DD_MISSILE_DAMAGE 1
#define DD_DEFENSE_RANGE 20
#define DD_ATTACK_RANGE 10
#define DD_DEFENSE_CD 60
#define DD_ATTACK_CD 15
#define DD_HP 2 

//Attack Definitions
#define DD_ATTACK_MODES 1
#define DD_ATK_MODE_1 "missile"


//Defense Definitions
#define DD_DEFENSE_MODES 1
#define DD_DEF_MODE_1 "lazer"

class DD :
	public vessel
{
public:
	DD();
	DD(string);
	DD(string, const _2D&);
	virtual ~DD();

	virtual bool defense(string, ...);//mode, va_list
	virtual missile* attack(string, ...)throw(int); //mode ,va_list
	virtual bool move(double, double);
protected:

	//ResourceClass
	virtual unsigned int PicSerial() { return PICS::PIC_DD; };
};


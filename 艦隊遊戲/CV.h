#pragma once
#include "vessel.h"
//Attributes
#define CV_MAX_SPEED 1
#define CV_MISSILE_SPEED 4
#define CV_MISSILE_DAMAGE 3
#define CV_DEFENSE_RANGE 5
#define CV_ATTACK_RANGE 25
#define CV_DEFENSE_CD 15
#define CV_ATTACK_CD 60
#define CV_HP 5

//Attack Definitions
#define CV_ATTACK_MODES 1
#define CV_ATK_MODE_1 "missile"


//Defense Definitions
#define CV_DEFENSE_MODES 1
#define CV_DEF_MODE_1 "lazer"

class CV :
	public vessel
{
public:
	CV();
	CV(string);
	CV(string, const _2D&);
	virtual ~CV();

	virtual bool defense(string, ...);//mode, va_list
	virtual missile* attack(string, ...)throw(int); //mode ,va_list
	virtual bool move(double, double);
protected:
	//ResourceClass
	virtual unsigned int PicSerial() { return PICS::PIC_CV; };
};


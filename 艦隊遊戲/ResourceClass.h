#pragma once


enum PICS
{
	//SYSTEM
	PIC_NON,
	//MISSILES
	PIC_BB,
	PIC_CG,
	PIC_DD,
	PIC_CV,
	//MISSILE
	PIC_MS,
	//EFFECTS
	PIC_MS_EX,
	//PIC_DEF_LAZER,
	//SYSTEM
	PIC_END
};

enum EFFECTS
{
	EF_UNKNOWN,
	EF_LINE,
	EF_ROUND_SHRINK,
	EF_ROUND_EXPAND,
	EF_END,
};

class ResourceClass
{
	
public:
	ResourceClass();
	~ResourceClass();
	virtual unsigned int PicSerial() { return 0; }
	virtual unsigned int EffectSerial() { return 0; }
};


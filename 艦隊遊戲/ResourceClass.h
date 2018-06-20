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
	
	//ATK WEAPONS
	PIC_ATK_MS,

	//DEF WEAPONS
	PIC_DEF_NOVA,

	//EFFECTS
	PIC_MS_EX,

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


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
	PIC_EX,

	//SYSTEM
	PIC_END
};

enum EFFECTS
{
	EF_LINE,
	EF_ROUND_SMALLER,
	EF_ROUND_LARGER,
	EF_END,
};

class ResourceClass
{
	
public:
	ResourceClass();
	~ResourceClass();
	virtual unsigned int PicSerial() { return 0; };
	
};


#pragma once
#include "effect.h"


class RoundShrink :
	public effect
{
	friend class MainForm;
public:
	RoundShrink();
	RoundShrink(unsigned int,double, const _2D&);//radius , Location
	~RoundShrink();

	virtual void tick();
	virtual bool dead();
private:
	double radius;
	_2D Location;

	virtual unsigned int EffectSerial() { return EFFECTS::EF_ROUND_SHRINK; }
};


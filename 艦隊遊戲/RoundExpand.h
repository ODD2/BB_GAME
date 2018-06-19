#pragma once
#include "effect.h"
class RoundExpand :
	public effect
{
	friend class MainForm;
public:
	RoundExpand();
	RoundExpand(unsigned int, double, const _2D&);//radius , Location
	~RoundExpand();

	virtual void tick();
	virtual bool dead();
private:
	double radius=0;
	double radius_limit=0;
	_2D Location;

	virtual unsigned int EffectSerial() { return EFFECTS::EF_ROUND_EXPAND; }
};


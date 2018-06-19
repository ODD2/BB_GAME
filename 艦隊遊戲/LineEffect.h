#pragma once
#include <string>
#include "location_system.h"
#include "qcolor.h"
#include "effect.h"
class LineEffect :
	public effect
{
	friend class MainForm;
public:
	LineEffect();
	LineEffect(QColor,double, double, _2D, _2D);//pic,duration,width,location,destination.
	~LineEffect();

	virtual void tick();
	virtual bool dead();
protected:
	_2D Location = {-1,-1};
	_2D Destination = { -1,-1 };
	double width = 0;
	double duration = 0;
	double tick_duration;
	QColor color;

	virtual unsigned int EffectType() { return EFFECTS::EF_LINE; }
};


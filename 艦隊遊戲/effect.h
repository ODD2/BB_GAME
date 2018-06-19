#pragma once

#include "location_system.h"
#include "ResourceClass.h"

class effect:public ResourceClass
{
	friend class MainForm;
	friend class BattleField;
public:
	effect();
	effect(unsigned int serial) :serial(serial) {};
	~effect();

	virtual void tick()=0;
	virtual bool dead() = 0;
protected:
	unsigned int serial = 0;

	//ResourceClass
	unsigned int PicSerial() { return serial; }
	virtual unsigned int EffectType() { return 0; }
};


#include "RoundExpand.h"
#define EXPAND_SPEED 0.05


RoundExpand::RoundExpand() :radius(0), Location(0, 0)
{
}

//radius , Location
RoundExpand::RoundExpand(unsigned int serial, double radius, const _2D& Location) : effect(serial), radius_limit(radius), Location(Location) {
}

RoundExpand::~RoundExpand()
{
}

bool RoundExpand::dead() {
	return radius_limit	<= radius;
}

void RoundExpand::tick() {
	radius += EXPAND_SPEED;
}
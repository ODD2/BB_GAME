#include "RoundShrink.h"
#define CONVERGE_SPEED 0.05


RoundShrink::RoundShrink():radius(0), Location(0, 0)
{
}

//radius , Location
RoundShrink::RoundShrink(unsigned int serial,double radius, const _2D& Location):effect(serial),radius(radius), Location(Location){
}

RoundShrink::~RoundShrink()
{
}

bool RoundShrink::dead() {
	return radius <= 0;
}

void RoundShrink::tick() {
	radius -= CONVERGE_SPEED;
}
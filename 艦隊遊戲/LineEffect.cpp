#include "LineEffect.h"

#define LINE_DURATION_DEC_RATE 0.01

LineEffect::LineEffect()
{
}

LineEffect::LineEffect( QColor color,double duration,double width, _2D loc, _2D des):
	color(color),duration(duration),width(width),Location(loc),Destination(des)
{
	tick_duration = duration;
}

LineEffect::~LineEffect()
{
}

void LineEffect::tick() {
	if (duration >= 0)
	{
		duration -= LINE_DURATION_DEC_RATE;
		color.setAlpha( duration/ tick_duration * 255);
	}
}

bool LineEffect::dead()
{
	return duration <= 0;
}
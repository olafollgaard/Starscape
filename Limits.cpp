#include "Limits.h"

void TransitionLimit::Interpolate(float pct,
	const TransitionLimit& a, const TransitionLimit& b)
{
	duration16ms = Interpolate8(pct, a.duration16ms, b.duration16ms);
	if (duration16ms < 1) duration16ms = 1;
	color.hue = Interpolate8(pct, a.color.hue, b.color.hue);
	color.bri = Interpolate8(pct, a.color.bri, b.color.bri);
}

uint8_t TransitionLimit::Interpolate8(float pct, int16_t a, int16_t b)
{
 	int16_t res = pct * (b - a) + a;
 	return res < 0 ? 0 : res > 0xFF ? 0xFF : res;
}

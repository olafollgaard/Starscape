#include "Limits.h"

void TransitionLimit::Interpolate(float pct,
	const TransitionLimit& a, const TransitionLimit& b)
{
	duration = InterpolateDuration(pct, a.duration, b.duration);
	color = InterpolateColor(pct, a.color, b.color);
}

uint8_t TransitionLimit::InterpolateDuration(
	float pct, int16_t a, int16_t b)
{
 	int16_t res = pct * (b - a) + a;
 	return res < 1 ? 1 : res > 0xFF ? 0xFF : res;
}

uint32_t TransitionLimit::InterpolateColor(
	float pct, uint32_t a, uint32_t b)
{
	color_t _a, _b, _res;
	_a.value = a;
	_b.value = b;
	for (uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		int16_t chA = _a.channel[ch];
		int16_t chB = _b.channel[ch];
		int16_t chR = pct * (chB - chA) + chA;
		chR = chR < 0 ? 0 : chR > 0xFF ? 0xFF : chR;
		_res.channel[ch] = (uint8_t)chR;
	}
	return _res.value;
}

#include "Color.h"

uint32_t color_t::Interpolate(float pct, uint32_t a, uint32_t b)
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

void transition_t::Init(uint32_t time, uint32_t value)
{
	timeMs = time;
	color.value = value;
}

uint32_t transition_t::InterpolateTimeMs(float pct, int32_t a, int32_t b)
{
	int32_t res = pct * (b - a) + a;
	return res < 0 ? 0 : res;
}

void transition_t::Interpolate(float pct, transition_t& dst, transition_t& a, transition_t& b)
{
	dst.color.value = color_t::Interpolate(pct, a.color.value, b.color.value);
	dst.timeMs = transition_t::InterpolateTimeMs(pct, a.timeMs, b.timeMs);
}
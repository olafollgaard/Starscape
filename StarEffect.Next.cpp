#include <Arduino.h>
#include "StarEffect.h"

void StarEffect::Next(transition_t& transition)
{
	const Limits* limits = &_activeLimits;
	if (_twinkle.CanStart()) {
		_twinkle.Start();
		limits = &twinkleLimits;
	}
	transition.duration = random(limits->lo.duration, limits->hi.duration);
	uint32_t lo = limits->lo.color;
	uint32_t hi = limits->hi.color;
	for (uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		transition.target[ch] = random((uint8_t)lo, (uint8_t)hi);
		lo >>= 8;
		hi >>= 8;
	}
}

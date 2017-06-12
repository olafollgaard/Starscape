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
		if ((uint8_t)hi < 0x80) {
			uint8_t next = 2 * random((uint8_t)lo, (uint8_t)hi);
			next = next < (uint8_t)hi ? 0 : next - (uint8_t)hi;
			transition.target[ch] = next;
		}
		else {
			transition.target[ch] = random((uint8_t)lo, (uint8_t)hi);
		}
		lo >>= 8;
		hi >>= 8;
	}
}

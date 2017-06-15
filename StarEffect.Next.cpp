#include <Arduino.h>
#include "StarEffect.h"

void StarEffect::Next(transition_t& transition)
{
	transition.origin = transition.target;
	const TransitionRange* range = &_activeRange;
	if (_twinkle.CanStart()) {
		_twinkle.Start();
		range = &twinkleRange;
	}
	transition.flags.hueDirectSpan = range->lo.color.hue <= range->hi.color.hue;
	uint16_t durationMs = random(
		(uint16_t)(range->lo.duration16ms) << 4,
		(uint16_t)(range->hi.duration16ms + 1) << 4);
	transition.flags.duration32ms = durationMs >> 5;
	hbr_t lo = range->lo.color;
	hbr_t hi = range->hi.color;
	transition.target.bri = random(0, 101) > range->pctOn ? 0
		: (uint8_t)random((uint16_t)lo.bri, (uint16_t)hi.bri + 1);
	transition.target.hue = lo.hue + (uint8_t)random(0, hi.hue + 1 - lo.hue);
}

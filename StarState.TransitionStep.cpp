#include "Arduino.h"
#include "StarState.h"

#define MIN_MS_BETWEEN_STEPS 10

bool StarState::TransitionStep(color_t& current)
{
	float nowPct = CalcElapsedPct();
	hbr_t &origin = _transition.origin;
	hbr_t &target = _transition.target;
	hbr_t next;
	next.bri = InterpolateByte(nowPct, origin.bri, target.bri);
	next.hue = _transition.flags.hueDirectSpan
		? InterpolateByte(nowPct, origin.hue, target.hue)
		: InterpolateByte(nowPct, 0, target.hue - origin.hue) + origin.hue;
	color_t nextColor;
	nextColor.SetColor(next);

	bool updated = false;
	for (uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		updated = updated || nextColor.channel[ch] != current.channel[ch];
		current.channel[ch] = nextColor.channel[ch];
	}
	return updated;
}

float StarState::CalcElapsedPct()
{
	uint8_t now16ms = (uint16_t)millis() >> 4;
	uint8_t duration16ms = _transition.flags.duration32ms << 1;
	uint8_t elapsed16ms = now16ms - _start16ms;
	float elapsedPct = elapsed16ms * 1.0 / duration16ms;
	return elapsedPct < 0 ? 0 : elapsedPct > 1 ? 1 : elapsedPct;
}

uint8_t StarState::InterpolateByte(float pct, int16_t a, int16_t b)
{
 	int16_t res = pct * (b - a) + a;
 	return res < 0 ? 0 : res > 0xFF ? 0xFF : res;
}

#include "Arduino.h"
#include "StarState.h"

#define MIN_MS_BETWEEN_STEPS 10

bool StarState::TransitionStep(color_t& current)
{
	uint16_t nowMs = millis();
	float nowPct = CalcElapsedPct(nowMs);

	bool updated = false;
	for (uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		float curr = current.channel[ch];
		float goal = _transition.target[ch];
		float org = _origin[ch];
		float next = org + (goal - org) * nowPct;
		uint8_t nextV = next < 0 ? 0 : next > 0xFF ? 0xFF : (uint8_t)next;
		if (nextV == curr) continue;
		updated = true;
		current.channel[ch] = nextV;
	}
	return updated;
}

float StarState::CalcElapsedPct(uint16_t timeMs)
{
	uint16_t durationMs = TRANSITION_DURATION_TO_MS(_transition.duration);
	uint16_t elapsedMs = timeMs - _startMs;
	float elapsedPct = elapsedMs * 1.0 / durationMs;
	return elapsedPct < 0 ? 0 : elapsedPct > 1 ? 1 : elapsedPct;
}
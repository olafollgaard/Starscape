#include "Arduino.h"
#include "StarState.h"

#define MIN_MS_BETWEEN_STEPS 10

bool StarState::TransitionStep(color_t& current)
{
	uint16_t nowMs = millis();
	uint8_t sinceLastMs = (uint8_t)nowMs - _lastUpdateMs;
	if (sinceLastMs < MIN_MS_BETWEEN_STEPS) return false;
	uint16_t currMs = nowMs - (uint16_t)sinceLastMs;
	uint16_t durationMs = TRANSITION_DURATION_TO_MS(_transition.duration);

	float nowPct = (nowMs - _startMs) / durationMs;
	float currPct = (currMs - _startMs) / durationMs;
	nowPct = nowPct < 0 ? 0 : nowPct > 1 ? 1 : 0;
	currPct = currPct < 0 ? 0 : currPct > 1 ? 1 : 0;

	bool updated = false;
	for (uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		int16_t curr = current.channel[ch];
		int16_t goal = _transition.target[ch];
		int16_t org = currPct <= 0 ? curr : currPct >= 1 ? goal :
			// curr == org + (goal - org) * currPct
			// curr / currPct == org / currPct + goal - org
			// curr / currPct - goal == org / currPct - org
			// curr / currPct - goal == org * (currPct - 1)
			// org ==
					  (curr / currPct - goal) / (currPct - 1);
		int16_t next = org + (goal - org) * nowPct;
		next = next < 0 ? 0 : next > 0xFF ? 0xFF : next;
		if (next == curr) continue;
		updated = true;
		current.channel[ch] = (uint8_t)next;
	}

	_lastUpdateMs = nowMs;
	return updated;
}

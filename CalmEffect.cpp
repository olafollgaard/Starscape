#include <Arduino.h>
#include "CalmEffect.h"

#define TRANSITION_MIN_MS 500
#define TRANSITION_MAX_MS 2000

void CalmEffect::Next(StarTransition& transition)
{
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		transition.goal.channel[ch] = random(256);
	}
	transition.timeMs = random(TRANSITION_MIN_MS, TRANSITION_MAX_MS);
}
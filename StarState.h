#ifndef _STARSTATE_H
#define _STARSTATE_H

#include <Adafruit_NeoPixel.h>
#include "Color.h"
#include "StarEffect.h"

class StarState {
public:
	bool Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect);

private:
	transition_t _transition;
	// Cut off at 16 bits: 65535 ms = just over one mitute = good enough
	uint16_t _startMs;
	// Cut off at 8 bits: 256 ms
	uint8_t _lastUpdateMs;

	void UpdateTransition(StarEffect* effect);
	bool TransitionStep(color_t& current);
};

#endif
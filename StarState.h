#ifndef _STARSTATE_H
#define _STARSTATE_H

#include <Adafruit_NeoPixel.h>
#include "Color.h"
#include "StarEffect.h"

class StarState {
public:
	bool Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect);

	transition_t _transition;
	// Start time, resolution 16 ms, max period = 256 * 16 ms = 4096 ms
	uint8_t _start16ms;

private:
	bool TransitionStep(color_t& current);
	float CalcElapsedPct();
	uint8_t InterpolateByte(float pct, int16_t a, int16_t b);
};

#endif
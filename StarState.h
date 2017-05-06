#ifndef _STARSTATE_H
#define _STARSTATE_H

#include <Adafruit_NeoPixel.h>
#include "Color.h"
#include "StarEffect.h"

class StarState {
public:
	bool Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect);

private:
	uint32_t _startMs;
	color_t _origin;
	transition_t _transition;
	void NextTransition(color_t& current, StarEffect* effect);
	bool TransitionStep(color_t& current);
};

#endif
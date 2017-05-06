#ifndef _STARSTATE_H
#define _STARSTATE_H

#include <Adafruit_NeoPixel.h>
#include "StarValue.h"
#include "StarEffect.h"

class StarState {
public:
	bool Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect);

private:
	unsigned long _startMs;
	StarColor _origin;
	StarTransition _transition;
	void NextTransition(StarColor& current, StarEffect* effect);
	bool TransitionStep(StarColor& current);
	bool TransitionStepChannel(StarColor& current, uint8_t ch, float pct);
};

#endif
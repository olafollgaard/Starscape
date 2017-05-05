#ifndef _STARSTATE_H
#define _STARSTATE_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Constants.h"

union StarColor {
	uint8_t channel[CHANNELS_PER_PIXEL];
	uint32_t color;
};

struct StarTransition {
	unsigned long timeMs;
	StarColor goal;
};

class StarState {
public:
	bool Update(Adafruit_NeoPixel& strip, uint16_t n);

private:
	unsigned long _startMs;
	StarColor _origin;
	StarTransition _transition;
	void Reset(StarColor& current);
	bool UpdateTransition(StarColor& current);
	bool UpdateChannelTransition(StarColor& current, uint8_t ch, float pct);
};

#endif
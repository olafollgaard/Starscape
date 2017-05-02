#ifndef _STAR_H
#define _STAR_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Constants.h"

union StarColor {
	uint8_t channel[CHANNELS_PER_PIXEL];
	uint32_t color;
};

class Star {
public:
	bool Update(Adafruit_NeoPixel& strip, uint16_t n);

private:
	unsigned long _startMs, _transitionMs;
	StarColor _from, _to;
	void Reset(StarColor& current);
	bool UpdateTransition(StarColor& current);
	bool UpdateChannelTransition(StarColor& current, uint8_t ch, float pct);
};

#endif
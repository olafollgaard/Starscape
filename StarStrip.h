#ifndef _STARSTRIP_H
#define _STARSTRIP_H

#include <Adafruit_NeoPixel.h>
#include "StarState.h"
#include "StarEffect.h"

#define STRIP_LENGTH 60

class StarStrip {
public:
	StarStrip(uint8_t pin);
	void Update(StarEffect* effect);

	Adafruit_NeoPixel _strip;
	uint8_t _pixels[STRIP_LENGTH * CHANNELS_PER_PIXEL];
	StarState _states[STRIP_LENGTH];
};

#endif
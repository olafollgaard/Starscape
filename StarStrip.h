#ifndef _STARSTRIP_H
#define _STARSTRIP_H

#include <Adafruit_NeoPixel.h>
#include "StarState.h"
#include "StarEffect.h"

#define STRIP_LENGTH 120

class StarStrip {
public:
	StarStrip(uint8_t pin);
	void Update(StarEffect* effect);

private:
	Adafruit_NeoPixel _strip;
	StarState _states[STRIP_LENGTH];
};

#endif
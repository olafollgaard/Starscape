#ifndef _STARSTRIP_H
#define _STARSTRIP_H

#include <Adafruit_NeoPixel.h>
#include "StarState.h"
#include "StarEffect.h"

class StarStrip {
public:
	StarStrip(uint16_t n, uint8_t pin);
	void Update(StarEffect* effect);

private:
	uint16_t _length;
	Adafruit_NeoPixel _strip;
	StarState* _states;
};

#endif
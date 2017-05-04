#ifndef _STARSTRIP_H
#define _STARSTRIP_H

#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include "Star.h"

class StarStrip {
public:
	StarStrip(uint16_t n, uint8_t pin);
	void Update();

private:
	uint16_t _length;
	Adafruit_NeoPixel _strip;
	Star* _stars;
};

#endif
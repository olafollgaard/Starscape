#ifndef _STARSTRIP_H
#define _STARSTRIP_H

#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include "Star.h"

class StarStrip {
public:
	StarStrip();
	void Update();

private:
	Adafruit_NeoPixel _strip = Adafruit_NeoPixel(
		STARSTRIP_LENGTH, STARSTRIP_PIN, NEO_GRB | NEO_KHZ800);
	Star _stars[STARSTRIP_LENGTH];
};

#endif
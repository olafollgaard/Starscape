#include "Arduino.h"
#include "StarState.h"

bool StarState::Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect)
{
	color_t current;
	current.value = strip.getPixelColor(n);
	if (CalcElapsedPct() >= 1.0) {
		effect->Next(_transition);
		_start16ms = millis() >> 4;
	}
	if (!TransitionStep(current)) return false;
	strip.setPixelColor(n, current.value);
	return true;
}

#include "StarStrip.h"

StarStrip::StarStrip(uint8_t pin)
	: _strip(STRIP_LENGTH, pin, NEO_GRB | NEO_KHZ800)
{
	_strip.begin();
	_strip.clear();
}

void StarStrip::Update(StarEffect* effect)
{
	bool updated = false;
	for (uint16_t i = 0; i < STRIP_LENGTH; i++) {
		if (_states[i].Update(_strip, i, effect)) updated = true;
	}
	if (updated) _strip.show();
}

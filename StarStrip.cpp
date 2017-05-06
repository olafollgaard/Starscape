#include "StarStrip.h"

StarStrip::StarStrip(uint16_t n, uint8_t pin)
	: _strip(n, pin, NEO_GRB | NEO_KHZ800)
{
	_length = n;
	_states = new StarState[n];
	_strip.begin();
	_strip.clear();
}

void StarStrip::Update(StarEffect* effect)
{
	bool updated = false;
	for (uint16_t i = 0; i < _length; i++) {
		if (_states[i].Update(_strip, i, effect)) updated = true;
	}
	if (updated) _strip.show();
}

#include "StarStrip.h"

StarStrip::StarStrip(uint16_t n, uint8_t pin)
	: _strip(n, pin, NEO_GRB | NEO_KHZ800)
{
	_length = n;
	_stars = new Star[n];
	_strip.begin();
	_strip.clear();
}

void StarStrip::Update()
{
	bool updated = false;
	for (uint16_t i = 0; i < _length; i++) {
		if (_stars[i].Update(_strip, i)) updated = true;
	}
	if (updated) _strip.show();
}

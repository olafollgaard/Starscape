#include "StarStrip.h"

StarStrip::StarStrip()
{
	_strip.begin();
	_strip.clear();
}

void StarStrip::Update()
{
	bool updated = false;
	for (uint16_t i = 0; i < STARSTRIP_LENGTH; i++) {
		if (_stars[i].Update(_strip, i)) updated = true;
	}
	if (updated) _strip.show();
}

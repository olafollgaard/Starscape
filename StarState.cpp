#include "Arduino.h"
#include "StarState.h"

bool StarState::Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect)
{
	color_t current;
	current.value = strip.getPixelColor(n);
	if (millis() - _startMs >= _transition.timeMs) NextTransition(current, effect);
	if (!TransitionStep(current)) return false;
	strip.setPixelColor(n, current.value);
	return true;
}

void StarState::NextTransition(color_t& current, StarEffect* effect)
{
	_origin = current;
	effect->Next(_transition);
	_startMs = millis();
}

bool StarState::TransitionStep(color_t& current)
{
	float pct = (millis() - _startMs) / _transition.timeMs;
	pct = pct < 0 ? 0 : pct > 1 ? 1 : pct;
	uint32_t prev = current.value;
	current.value = color_t::Interpolate(pct, _origin.value, _transition.color.value);
	return current.value != prev;
}

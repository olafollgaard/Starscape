#include "Arduino.h"
#include "StarState.h"

bool StarState::Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect)
{
	color_t current;
	current.value = strip.getPixelColor(n);
	UpdateTransition(effect);
	if (!TransitionStep(current)) return false;
	strip.setPixelColor(n, current.value);
	return true;
}

void StarState::UpdateTransition(StarEffect* effect)
{
	uint16_t nowMs = millis();
	uint16_t transitionDurationMs =
		TRANSITION_DURATION_TO_MS((uint16_t)(_transition.duration));
	if (nowMs - _startMs < transitionDurationMs) return;
	effect->Next(_transition);
	_startMs = millis();
	_lastUpdateMs = _startMs;
}

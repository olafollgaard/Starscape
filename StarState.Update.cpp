#include "Arduino.h"
#include "StarState.h"

bool StarState::Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect)
{
	color_t current;
	current.value = strip.getPixelColor(n);
	if (UpdateTransition(effect)) {
		for (uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
			_origin[ch] = current.channel[ch];
		}
	}
	if (!TransitionStep(current)) return false;
	strip.setPixelColor(n, current.value);
	return true;
}

bool StarState::UpdateTransition(StarEffect* effect)
{
	uint16_t nowMs = millis();
	uint16_t transitionDurationMs =
		TRANSITION_DURATION_TO_MS((uint16_t)(_transition.duration));
	if (nowMs - _startMs < transitionDurationMs) return false;
	effect->Next(_transition);
	_startMs = millis();
	return true;
}

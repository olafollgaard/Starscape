#include "Arduino.h"
#include "StarState.h"

bool StarState::Update(Adafruit_NeoPixel& strip, uint16_t n, StarEffect* effect)
{
	StarColor current;
	current.color = strip.getPixelColor(n);
	if (millis() - _startMs >= _transition.timeMs) NextTransition(current, effect);
	if (!TransitionStep(current)) return false;
	strip.setPixelColor(n, current.color);
	return true;
}

void StarState::NextTransition(StarColor& current, StarEffect* effect)
{
	_origin = current;
	effect->Next(_transition);
	_startMs = millis();
}

bool StarState::TransitionStep(StarColor& current)
{
	float pct = (millis() - _startMs) / _transition.timeMs;
	bool updated = false;
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		if(TransitionStepChannel(current, ch, pct)) updated = true;
	}
	return updated;
}

bool StarState::TransitionStepChannel(StarColor& current, uint8_t ch, float pct)
{
	uint8_t prev = current.channel[ch];
	int16_t value = (_transition.goal.channel[ch] - _origin.channel[ch]) * pct + _origin.channel[ch];
	value = value < 0 ? 0 : value > 0xFF ? 0xFF : value;
	current.channel[ch] = (uint8_t)value;
	return current.channel[ch] != prev;
}

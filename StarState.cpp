#include "Arduino.h"
#include "StarState.h"

bool StarState::Update(Adafruit_NeoPixel& strip, uint16_t n)
{
	StarColor current;
	current.color = strip.getPixelColor(n);
	if (millis() - _startMs >= _transition.timeMs) Reset(current);
	if (!UpdateTransition(current)) return false;
	strip.setPixelColor(n, current.color);
	return true;
}

void StarState::Reset(StarColor& current)
{
	_origin = current;
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		_transition.goal.channel[ch] = random(256);
	}
	_transition.timeMs = random(STAR_TRANSITION_MIN_MS, STAR_TRANSITION_MAX_MS);
	_startMs = millis();
}

bool StarState::UpdateTransition(StarColor& current)
{
	unsigned long now = millis();
	float pct = (now - _startMs) / _transition.timeMs;
	bool updated = false;
	// Step all channels, don't reduce to boolean short-circuit
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		if(UpdateChannelTransition(current, ch, pct)) updated = true;
	}
	return updated;
}

bool StarState::UpdateChannelTransition(StarColor& current, uint8_t ch, float pct)
{
	uint8_t prev = current.channel[ch];
	int16_t value = (_transition.goal.channel[ch] - _origin.channel[ch]) * pct + _origin.channel[ch];
	value = value < 0 ? 0 : value > 0xFF ? 0xFF : value;
	current.channel[ch] = (uint8_t)value;
	return current.channel[ch] != prev;
}

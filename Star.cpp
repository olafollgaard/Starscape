#include "Arduino.h"
#include "Star.h"

bool Star::Update(Adafruit_NeoPixel& strip, uint16_t n)
{
	StarColor current;
	current.color = strip.getPixelColor(n);
	if (millis() - _startMs >= _transitionMs) Reset(current);
	if (!UpdateTransition(current)) return false;
	strip.setPixelColor(n, current.color);
	return true;
}

void Star::Reset(StarColor& current)
{
	_from = current;
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		_to.channel[ch] = random(256);
	}
	_transitionMs = random(STAR_TRANSITION_MIN_MS, STAR_TRANSITION_MAX_MS);
	_startMs = millis();
}

bool Star::UpdateTransition(StarColor& current)
{
	unsigned long now = millis();
	float pct = (now - _startMs) / _transitionMs;
	bool updated = false;
	// Step all channels, don't reduce to boolean short-circuit
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		if(UpdateChannelTransition(current, ch, pct)) updated = true;
	}
	return updated;
}

bool Star::UpdateChannelTransition(StarColor& current, uint8_t ch, float pct)
{
	uint8_t prev = current.channel[ch];
	current.channel[ch] = (_to.channel[ch] - _from.channel[ch]) * pct + _from.channel[ch];
	return current.channel[ch] != prev;
}

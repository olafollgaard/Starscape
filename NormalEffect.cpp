#include <Arduino.h>
#include "NormalEffect.h"

void NormalEffect::Update()
{
	time_t timeOfDay = now();
	timeOfDay -= previousMidnight(timeOfDay);

	PeriodId oldPeriod = _activePeriod;
	_activePeriod = GetPeriod(timeOfDay);
	if (_activePeriod != oldPeriod || !_activeLevelsInitialized) {
		_activeLevelsInitialized = true;
		_activeLevels.lo = periods[_activePeriod].lo;
		_activeLevels.hi = periods[_activePeriod].hi;
	}
	else {
		time_t transitionStart = periods[_activePeriod].endTimeOfDay - periodTransitionDuration;
		if (timeOfDay > transitionStart) {
			time_t transitionStep = timeOfDay - transitionStart;
			PeriodTransitionStep(transitionStep / periodTransitionDuration);
		}
	}
}

void NormalEffect::Next(transition_t& transition)
{
	const Levels* levels = &_activeLevels;
	if (periods[_activePeriod].hi.color.value != 0 && _twinkle.CanStart()) {
		_twinkle.Start();
		levels = &twinkleLevels;
	}
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		transition.color.channel[ch] = random(
			levels->lo.color.channel[ch], levels->hi.color.channel[ch]);
	}
	transition.timeMs = random(levels->lo.timeMs, levels->hi.timeMs);
}

NormalEffect::PeriodId NormalEffect::GetPeriod(time_t timeOfDay)
{
	for (uint8_t res = 0; res < PERIOD_COUNT; res++) {
		if (timeOfDay < periods[res].endTimeOfDay) return (PeriodId)res;
	}
	return (PeriodId)0;
}

void NormalEffect::PeriodTransitionStep(float pct)
{
	pct = pct < 0 ? 0 : pct > 1 ? 1 : pct;
	uint8_t nextPeriod = (uint8_t)_activePeriod + 1;
	if (nextPeriod == PERIOD_COUNT) nextPeriod = 0;
	transition_t::Interpolate(pct, _activeLevels.lo,
		periods[_activePeriod].lo, periods[nextPeriod].lo);
	transition_t::Interpolate(pct, _activeLevels.hi,
		periods[_activePeriod].hi, periods[nextPeriod].hi);
}

bool NormalEffect::Twinkle::CanStart()
{
	return (millis() - currStartMs) > currIntervalMs;
}

void NormalEffect::Twinkle::Start()
{
	currStartMs = millis();
	currIntervalMs = random(twinkleMinIntervalMs, twinkleMaxIntervalMs);
}
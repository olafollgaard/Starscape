#include <Arduino.h>
#include "StarEffect.h"

void StarEffect::Update()
{
	PeriodId oldPeriod = _activePeriod;
	uint8_t h = hour();
	uint8_t m = minute();
	_activePeriod = GetPeriod(MAKE_TIMEOFDAY(h * 100 + m));
	if (_activePeriod != oldPeriod || _activeRange.lo.duration16ms == 0) {
		_activeRange = periodLimits[_activePeriod].range;
	}
	else {
		time_t endTOD = TIMEOFDAY2TIME(periodLimits[_activePeriod].endTimeOfDay);
		time_t nowTOD = now();
		nowTOD -= previousMidnight(nowTOD);
		if (endTOD - nowTOD < periodTransitionDuration) {
			time_t start = endTOD - periodTransitionDuration;
			PeriodTransitionStep((nowTOD - start) / periodTransitionDuration);
		}
	}
}

StarEffect::PeriodId StarEffect::GetPeriod(uint8_t timeOfDay)
{
	for (uint8_t res = 0; res < PERIOD_COUNT; res++) {
		if (timeOfDay < periodLimits[res].endTimeOfDay) return (PeriodId)res;
	}
	return (PeriodId)0;
}

void StarEffect::PeriodTransitionStep(float pct)
{
	pct = pct < 0 ? 0 : pct > 1 ? 1 : pct;
	uint8_t nextPeriod = (uint8_t)_activePeriod + 1;
	if (nextPeriod == PERIOD_COUNT) nextPeriod = 0;
	_activeRange.lo.Interpolate(pct,
		periodLimits[_activePeriod].range.lo, periodLimits[nextPeriod].range.lo);
	_activeRange.hi.Interpolate(pct,
		periodLimits[_activePeriod].range.hi, periodLimits[nextPeriod].range.hi);
}

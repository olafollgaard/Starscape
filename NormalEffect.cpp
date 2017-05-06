#include <Arduino.h>
#include "NormalEffect.h"

#define SimpleTimeOfDay(T) (((T) / 100) * SECS_PER_HOUR + ((T) % 100) * SECS_PER_MIN)

NormalEffect::NormalEffect()
{
	_periodTransitionDuration = 5 * SECS_PER_MIN;
	_periodLevels [PeriodId::Night   ].lo.Init( 1 * 60 * 1000, 0);
	_periodLevels [PeriodId::Night   ].hi.Init( 2 * 60 * 1000, 0);
	_periodEndTime[PeriodId::Night   ] = SimpleTimeOfDay(  700);
	_periodLevels [PeriodId::Morning ].lo.Init(  500, 0x808080);
	_periodLevels [PeriodId::Morning ].hi.Init( 1000, 0xC0C0C0);
	_periodEndTime[PeriodId::Morning ] = SimpleTimeOfDay(  830);
	_periodLevels [PeriodId::Daylight].lo.Init( 1 * 60 * 1000, 0);
	_periodLevels [PeriodId::Daylight].hi.Init( 2 * 60 * 1000, 0);
	_periodEndTime[PeriodId::Daylight] = SimpleTimeOfDay( 1530);
	_periodLevels [PeriodId::Evening ].lo.Init( 1000, 0x808080);
	_periodLevels [PeriodId::Evening ].hi.Init( 5000, 0xC0C0C0);
	_periodEndTime[PeriodId::Evening ] = SimpleTimeOfDay( 2100);
	_periodLevels [PeriodId::Late    ].lo.Init( 1000, 0x202020);
	_periodLevels [PeriodId::Late    ].hi.Init( 5000, 0x606060);
	_periodEndTime[PeriodId::Late    ] = SimpleTimeOfDay( 2230);
	_periodLevels [PeriodId::NightOwl].lo.Init( 1000,        0);
	_periodLevels [PeriodId::NightOwl].hi.Init( 5000, 0x404040);
	_periodEndTime[PeriodId::NightOwl] = SimpleTimeOfDay( 2330);
	_activeLevelsInitialized = false;
}

void NormalEffect::Update()
{
	time_t timeOfDay = now();
	timeOfDay -= previousMidnight(timeOfDay);

	PeriodId oldPeriod = _activePeriod;
	_activePeriod = GetPeriod(timeOfDay);
	if (_activePeriod != oldPeriod || !_activeLevelsInitialized) {
		_activeLevelsInitialized = true;
		_activeLevels = _periodLevels[_activePeriod];
	}
	else {
		time_t transitionStart = _periodEndTime[_activePeriod] - _periodTransitionDuration;
		if (timeOfDay > transitionStart) {
			time_t transitionStep = timeOfDay - transitionStart;
			PeriodTransitionStep(transitionStep / _periodTransitionDuration);
		}
	}
}

void NormalEffect::Next(transition_t& transition)
{
	for(uint8_t ch = 0; ch < CHANNELS_PER_PIXEL; ch++) {
		transition.color.channel[ch] = random(
			_activeLevels.lo.color.channel[ch],
			_activeLevels.hi.color.channel[ch]);
	}
	transition.timeMs = random(
		_activeLevels.lo.timeMs,
		_activeLevels.hi.timeMs);
}

NormalEffect::PeriodId NormalEffect::GetPeriod(time_t timeOfDay)
{
	for (uint8_t res = 0; res < PERIOD_COUNT; res++) {
		if (timeOfDay < _periodEndTime[res]) return (PeriodId)res;
	}
	return (PeriodId)0;
}

void NormalEffect::PeriodTransitionStep(float pct)
{
	pct = pct < 0 ? 0 : pct > 1 ? 1 : pct;
	uint8_t nextPeriod = (uint8_t)_activePeriod + 1;
	if (nextPeriod == PERIOD_COUNT) nextPeriod = 0;
	transition_t::Interpolate(pct, _activeLevels.lo,
		_periodLevels[_activePeriod].lo, _periodLevels[nextPeriod].lo);
	transition_t::Interpolate(pct, _activeLevels.hi,
		_periodLevels[_activePeriod].hi, _periodLevels[nextPeriod].hi);
}

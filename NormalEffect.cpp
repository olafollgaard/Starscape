#include <Arduino.h>
#include "NormalEffect.h"

#define SimpleTimeOfDay(T) (((T) / 100) * SECS_PER_HOUR + ((T) % 100) * SECS_PER_MIN)

const NormalEffect::Period NormalEffect::periods[] = {
	[NormalEffect::PeriodId::Night] = {
		.lo = { .timeMs = 1 * 60 * 1000, .color = { .value = 0 } },
		.hi = { .timeMs = 2 * 60 * 1000, .color = { .value = 0 } },
		.endTimeOfDay = SimpleTimeOfDay(  700)
	},
	[NormalEffect::PeriodId::Morning] = {
		.lo = { .timeMs =  500, .color = { .value = 0x808080 } },
		.hi = { .timeMs = 1000, .color = { .value = 0xC0C0C0 } },
		.endTimeOfDay = SimpleTimeOfDay(  830)
	},
	[NormalEffect::PeriodId::Daylight] = {
		.lo = { .timeMs = 1 * 60 * 1000, .color = { .value = 0 } },
		.hi = { .timeMs = 2 * 60 * 1000, .color = { .value = 0 } },
		.endTimeOfDay = SimpleTimeOfDay( 1530)
	},
	[NormalEffect::PeriodId::Evening] = {
		.lo = { .timeMs = 1000, .color = { .value = 0x808080 } },
		.hi = { .timeMs = 5000, .color = { .value = 0xC0C0C0 } },
		.endTimeOfDay = SimpleTimeOfDay( 2100)
	},
	[NormalEffect::PeriodId::Late] = {
		.lo = { .timeMs = 3000, .color = { .value = 0x202020 } },
		.hi = { .timeMs = 8000, .color = { .value = 0x606060 } },
		.endTimeOfDay = SimpleTimeOfDay( 2230)
	},
	[NormalEffect::PeriodId::NightOwl] = {
		.lo = { .timeMs = 3000, .color = { .value =        0 } },
		.hi = { .timeMs = 8000, .color = { .value = 0x404040 } },
		.endTimeOfDay = SimpleTimeOfDay( 2330)
	}
};
const time_t NormalEffect::periodTransitionDuration = 5 * SECS_PER_MIN;

const NormalEffect::Levels NormalEffect::twinkleLevels = {
	.lo = { .timeMs = 1000, .color = { .value = 0xC0C0C0 } },
	.hi = { .timeMs = 3000, .color = { .value = 0xFFFFFF } }
};
const uint32_t twinkleMinIntervalMs =   500;
const uint32_t twinkleMaxIntervalMs = 15000;

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
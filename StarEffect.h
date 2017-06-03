#ifndef _STAREFFECT_H
#define _STAREFFECT_H

#include "Color.h"
#include "Limits.h"
#include "Twinkle.h"
#include <Time.h>

class StarEffect {
public:
	void Update();
	void Next(transition_t& transition);

	enum PeriodId {
		Night, Morning, Daylight, Evening, Late, NightOwl,
		PERIOD_COUNT
	};

	static const PeriodLimits periodLimits[];
	static const time_t periodTransitionDuration;
	static const Limits twinkleLimits;

	PeriodId _activePeriod;
	Limits _activeLimits;
	Twinkle _twinkle;

private:
	PeriodId GetPeriod(uint8_t timeOfDay);
	void PeriodTransitionStep(float pct);
};

#endif
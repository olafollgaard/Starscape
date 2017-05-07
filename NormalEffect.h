#ifndef _NORMALEFFECT_H
#define _NORMALEFFECT_H

#include "StarEffect.h"
#include <Time.h>

class NormalEffect : public StarEffect {
public:
	NormalEffect();
	void Update();
	void Next(transition_t& transition);

private:
	enum PeriodId {
		Night, Morning, Daylight, Evening, Late, NightOwl,
		PERIOD_COUNT
	};

	struct Levels {
		transition_t lo, hi;
	};

	struct Twinkle {
		Levels levels;
		uint32_t currStartMs, currIntervalMs, minIntervalMs, maxIntervalMs;
		bool CanStart();
		void Start();
	};

private:
	time_t _periodEndTime[PERIOD_COUNT];
	Levels _periodLevels[PERIOD_COUNT];
	PeriodId _activePeriod;
	time_t _periodTransitionDuration;
	Levels _activeLevels;
	bool _activeLevelsInitialized;
	Twinkle _twinkle;

	PeriodId GetPeriod(time_t timeOfDay);
	void PeriodTransitionStep(float pct);
};

#endif
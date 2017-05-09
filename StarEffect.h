#ifndef _STAREFFECT_H
#define _STAREFFECT_H

#include "Color.h"
#include <Time.h>

class StarEffect {
public:
	void Update();
	void Next(transition_t& transition);

private:
	enum PeriodId {
		Night, Morning, Daylight, Evening, Late, NightOwl,
		PERIOD_COUNT
	};

	struct Period {
		transition_t lo, hi;
		time_t endTimeOfDay;
	};

	struct Levels {
		transition_t lo, hi;
	};

	struct Twinkle {
		uint32_t currStartMs, currIntervalMs;
		bool CanStart();
		void Start();
	};

	static const Period periods[];
	static const time_t periodTransitionDuration;
	static const Levels twinkleLevels;
	static const uint32_t twinkleMinIntervalMs;
	static const uint32_t twinkleMaxIntervalMs;

private:
	PeriodId _activePeriod;
	Levels _activeLevels;
	bool _activeLevelsInitialized;
	Twinkle _twinkle;

	PeriodId GetPeriod(time_t timeOfDay);
	void PeriodTransitionStep(float pct);
};

#endif
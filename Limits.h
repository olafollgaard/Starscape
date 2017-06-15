#ifndef _LIMITS_H
#define _LIMITS_H

#include "Color.h"

struct TransitionLimit {
	// duration in 16 ms resolution
	uint8_t duration16ms;
	// color
	hbr_t color;
	void Interpolate(float pct,
		const TransitionLimit& a, const TransitionLimit& b);
	uint8_t Interpolate8(float pct, int16_t a, int16_t b);
};

struct TransitionRange {
	TransitionLimit lo, hi;
	// probability of pixels being turned on
	uint8_t pctOn;
};

struct PeriodLimits {
	TransitionRange range;
	// period end time in 10 min resolution (24h * 6 = 144 steps)
	uint8_t endTimeOfDay;
	#define MAKE_TIMEOFDAY(T) (((T) / 100) * 6 + ((T) % 100) / 10)
	#define TIMEOFDAY2TIME(T) ((T) * 10 * SECS_PER_MIN)
};

#endif
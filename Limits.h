#ifndef _LIMITS_H
#define _LIMITS_H

#include "Color.h"

struct TransitionLimit {
	// duration in 256 ms resolution
	uint8_t duration : 8;
	// color
	uint32_t color : 8 * CHANNELS_PER_PIXEL;
	void Interpolate(float pct,
		const TransitionLimit& a, const TransitionLimit& b);
	uint8_t InterpolateDuration(float pct, int16_t a, int16_t b);
	uint32_t InterpolateColor(float pct, uint32_t a, uint32_t b);
};

struct PeriodLimits {
	TransitionLimit lo, hi;
	// period end time in 10 min resolution (24h * 6 = 144 steps)
	uint8_t endTimeOfDay;
	#define MAKE_TIMEOFDAY(T) (((T) / 100) * 6 + ((T) % 100) / 10)
	#define TIMEOFDAY2TIME(T) ((T) * 10 * SECS_PER_MIN)
};

struct Limits {
	TransitionLimit lo, hi;
};

#endif
#include "StarEffect.h"

const PeriodLimits StarEffect::periodLimits[] = {
	[Night] = {
		.lo = { .duration = MS_TO_TRANSITION_DURATION( 30000 ), .color =        0 },
		.hi = { .duration = MS_TO_TRANSITION_DURATION( 60000 ), .color =        0 },
		.endTimeOfDay = MAKE_TIMEOFDAY(  700 )
	},
	[Morning] = {
		.lo = { .duration = MS_TO_TRANSITION_DURATION(   600 ), .color = 0x808080 },
		.hi = { .duration = MS_TO_TRANSITION_DURATION(  1200 ), .color = 0xC0C0C0 },
		.endTimeOfDay = MAKE_TIMEOFDAY(  830 )
	},
	[Daylight] = {
		.lo = { .duration = MS_TO_TRANSITION_DURATION( 30000 ), .color =        0 },
		.hi = { .duration = MS_TO_TRANSITION_DURATION( 60000 ), .color =        0 },
		.endTimeOfDay = MAKE_TIMEOFDAY( 1530 )
	},
	[Evening] = {
		.lo = { .duration = MS_TO_TRANSITION_DURATION(  1200 ), .color = 0x808080 },
		.hi = { .duration = MS_TO_TRANSITION_DURATION(  5200 ), .color = 0xC0C0C0 },
		.endTimeOfDay = MAKE_TIMEOFDAY( 2100 )
	},
	[Late] = {
		.lo = { .duration = MS_TO_TRANSITION_DURATION(  3000 ), .color = 0x202020 },
		.hi = { .duration = MS_TO_TRANSITION_DURATION(  9000 ), .color = 0x606060 },
		.endTimeOfDay = MAKE_TIMEOFDAY( 2230 )
	},
	[NightOwl] = {
		.lo = { .duration = MS_TO_TRANSITION_DURATION(  3000 ), .color =        0 },
		.hi = { .duration = MS_TO_TRANSITION_DURATION(  9000 ), .color = 0x404040 },
		.endTimeOfDay = MAKE_TIMEOFDAY( 2330 )
	}
};
const time_t StarEffect::periodTransitionDuration = 5 * SECS_PER_MIN;

const Limits StarEffect::twinkleLimits = {
	.lo = { .duration = MS_TO_TRANSITION_DURATION(  1200), .color = 0xC0C0C0 },
	.hi = { .duration = MS_TO_TRANSITION_DURATION(  3000), .color = 0xFFFFFF }
};
const uint32_t Twinkle::minIntervalMs =   500;
const uint32_t Twinkle::maxIntervalMs = 15000;

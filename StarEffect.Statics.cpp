#include "StarEffect.h"

// LEDs hues are: Warm white @ 0, Cold white @ 85, Amber @ 170
const PeriodLimits StarEffect::periodLimits[] = {
	[Night] = {
		.range = {
			.lo = { .duration16ms = 3000 >> 4, .color = { .hue = 170, .bri =    0 } },
			.hi = { .duration16ms = 4000 >> 4, .color = { .hue =   0, .bri =    0 } },
			.pctOn = 15
		},
		.endTimeOfDay = MAKE_TIMEOFDAY(  700 )
	},
	[Morning] = {
		.range = {
			.lo = { .duration16ms =  600 >> 4, .color = { .hue =   0, .bri =    0 } },
			.hi = { .duration16ms = 1200 >> 4, .color = { .hue =  85, .bri = 0x60 } },
			.pctOn = 75
		},
		.endTimeOfDay = MAKE_TIMEOFDAY(  830 )
	},
	[Daylight] = {
		.range = {
			.lo = { .duration16ms =  500 >> 4, .color = { .hue =   0, .bri =    0 } },
			.hi = { .duration16ms = 3000 >> 4, .color = { .hue =  85, .bri =    0 } },
			.pctOn = 50
		},
		.endTimeOfDay = MAKE_TIMEOFDAY( 1530 )
	},
	[Evening] = {
		.range = {
			.lo = { .duration16ms =  600 >> 4, .color = { .hue = 212, .bri =    0 } },
			.hi = { .duration16ms = 3200 >> 4, .color = { .hue = 127, .bri = 0x40 } },
			.pctOn = 50
		},
		.endTimeOfDay = MAKE_TIMEOFDAY( 2100 )
	},
	[Late] = {
		.range = {
			.lo = { .duration16ms = 1000 >> 4, .color = { .hue = 170, .bri =    0 } },
			.hi = { .duration16ms = 4000 >> 4, .color = { .hue =   0, .bri = 0x20 } },
			.pctOn = 25
		},
		.endTimeOfDay = MAKE_TIMEOFDAY( 2230 )
	},
	[NightOwl] = {
		.range = {
			.lo = { .duration16ms = 1000 >> 4, .color = { .hue = 170, .bri =    0 } },
			.hi = { .duration16ms = 4000 >> 4, .color = { .hue = 212, .bri = 0x10 } },
			.pctOn = 15
		},
		.endTimeOfDay = MAKE_TIMEOFDAY( 2330 )
	}
};
const time_t StarEffect::periodTransitionDuration = 5 * SECS_PER_MIN;

const TransitionRange StarEffect::twinkleRange = {
	.lo = { .duration16ms =  600 >> 4, .color = { .hue =  0, .bri = 0xC0 } },
	.hi = { .duration16ms = 2000 >> 4, .color = { .hue = 85, .bri = 0xFF } },
	.pctOn = 100
};
const uint32_t Twinkle::minIntervalMs =   500;
const uint32_t Twinkle::maxIntervalMs = 20000;

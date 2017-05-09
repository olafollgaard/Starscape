#include "StarEffect.h"

#define SimpleTimeOfDay(T) (((T) / 100) * SECS_PER_HOUR + ((T) % 100) * SECS_PER_MIN)

const StarEffect::Period StarEffect::periods[] = {
	[Night] = {
		.lo = { .timeMs = 1 * 60 * 1000, .color = { .value = 0 } },
		.hi = { .timeMs = 2 * 60 * 1000, .color = { .value = 0 } },
		.endTimeOfDay = SimpleTimeOfDay(  700)
	},
	[Morning] = {
		.lo = { .timeMs =  500, .color = { .value = 0x808080 } },
		.hi = { .timeMs = 1000, .color = { .value = 0xC0C0C0 } },
		.endTimeOfDay = SimpleTimeOfDay(  830)
	},
	[Daylight] = {
		.lo = { .timeMs = 1 * 60 * 1000, .color = { .value = 0 } },
		.hi = { .timeMs = 2 * 60 * 1000, .color = { .value = 0 } },
		.endTimeOfDay = SimpleTimeOfDay( 1530)
	},
	[Evening] = {
		.lo = { .timeMs = 1000, .color = { .value = 0x808080 } },
		.hi = { .timeMs = 5000, .color = { .value = 0xC0C0C0 } },
		.endTimeOfDay = SimpleTimeOfDay( 2100)
	},
	[Late] = {
		.lo = { .timeMs = 3000, .color = { .value = 0x202020 } },
		.hi = { .timeMs = 8000, .color = { .value = 0x606060 } },
		.endTimeOfDay = SimpleTimeOfDay( 2230)
	},
	[NightOwl] = {
		.lo = { .timeMs = 3000, .color = { .value =        0 } },
		.hi = { .timeMs = 8000, .color = { .value = 0x404040 } },
		.endTimeOfDay = SimpleTimeOfDay( 2330)
	}
};
const time_t StarEffect::periodTransitionDuration = 5 * SECS_PER_MIN;

const StarEffect::Levels StarEffect::twinkleLevels = {
	.lo = { .timeMs = 1000, .color = { .value = 0xC0C0C0 } },
	.hi = { .timeMs = 3000, .color = { .value = 0xFFFFFF } }
};
const uint32_t StarEffect::twinkleMinIntervalMs =   500;
const uint32_t StarEffect::twinkleMaxIntervalMs = 15000;

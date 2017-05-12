#ifndef _COLOR_H
#define _COLOR_H

#include <stdint.h>

// N.B. 32-bit pixels of 8-bit channels = max 4 channels
#define CHANNELS_PER_PIXEL 3

union color_t {
	uint8_t channel[CHANNELS_PER_PIXEL];
	uint32_t value;
};

#define MS_TO_TRANSITION_DURATION(MS) (MS >> 8)
#define TRANSITION_DURATION_TO_MS(D) (D << 8)

struct transition_t {
	// duration in 256 ms resolution
	uint8_t duration;
	// target color
	uint8_t target[CHANNELS_PER_PIXEL];
};

#endif
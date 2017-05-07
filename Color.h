#ifndef _COLOR_H
#define _COLOR_H

#include <stdint.h>

// N.B. 32-bit pixels of 8-bit channels = max 4 channels
#define CHANNELS_PER_PIXEL 3

union color_t {
	uint8_t channel[CHANNELS_PER_PIXEL];
	uint32_t value;
	static uint32_t Interpolate(float pct, uint32_t a, uint32_t b);
};

struct transition_t {
	uint32_t timeMs;
	color_t color;
	void Init(uint32_t time, uint32_t value);
	static uint32_t InterpolateTimeMs(float pct, int32_t a, int32_t b);
	static void Interpolate(float pct, transition_t& res,
		const transition_t& a, const transition_t& b);
};

#endif
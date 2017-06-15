#ifndef _COLOR_H
#define _COLOR_H

#include <stdint.h>

// N.B. 32-bit pixels of 8-bit channels = max 4 channels
#define CHANNELS_PER_PIXEL 3

// Hue and Brightness, omit Saturation
struct hbr_t {
	uint8_t hue;
	uint8_t bri;
	void Set_uint16(uint16_t v) { hue = (uint8_t)v; bri = (uint8_t)(v >> 8); }
	uint16_t Get_uint16() { return (uint16_t)hue | (uint16_t)bri << 8; }
};

union color_t {
	uint8_t channel[CHANNELS_PER_PIXEL];
	uint32_t value;
	void SetColor(hbr_t hbr);
};

struct transitionFlags_t {
	bool hueDirectSpan : 1;
	// duration in 32 ms resolution
	uint8_t duration32ms : 7;
};

struct transition_t {
	transitionFlags_t flags;
	// color origin
	hbr_t origin;
	// target color
	hbr_t target;
};

#endif
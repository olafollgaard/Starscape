#ifndef _STARVALUE_H
#define _STARVALUE_H

#include <stdint.h>
#include "Constants.h"

union StarColor {
	uint8_t channel[CHANNELS_PER_PIXEL];
	uint32_t color;
};

struct StarTransition {
	unsigned long timeMs;
	StarColor goal;
};

#endif
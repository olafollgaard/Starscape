#ifndef _TWINKLE_H
#define _TWINKLE_H

#include <stdint.h>

struct Twinkle {
	uint32_t currStartMs, currIntervalMs;
	bool CanStart();
	void Start();
	static const uint32_t minIntervalMs;
	static const uint32_t maxIntervalMs;
};

#endif
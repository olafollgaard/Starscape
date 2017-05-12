#include <Arduino.h>
#include "Twinkle.h"

bool Twinkle::CanStart()
{
	return (millis() - currStartMs) > currIntervalMs;
}

void Twinkle::Start()
{
	currStartMs = millis();
	currIntervalMs = random(minIntervalMs, maxIntervalMs);
}
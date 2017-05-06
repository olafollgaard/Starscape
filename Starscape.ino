#include "StarStrip.h"
#include <stdio.h>

#include "CalmEffect.h"

// Split into two strips for A/B testing
StarStrip *starStripA, *starStripB;
StarEffect *starEffectA, *starEffectB;

void setup()
{
	randomSeed(42);
	starStripA = new StarStrip(60, 5);
	starStripB = new StarStrip(60, 6);
	starEffectA = new CalmEffect();
	starEffectB = new CalmEffect();
}

void loop()
{
	starEffectA->Update();
	starEffectB->Update();
	unsigned long start = millis();
	starStripA->Update(starEffectA);
	starStripB->Update(starEffectB);
	unsigned long elapsed = millis() - start;
	if (elapsed < 5) delay(5 - elapsed);
}

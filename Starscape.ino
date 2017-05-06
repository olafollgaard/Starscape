#include "StarStrip.h"
#include <stdio.h>
#include <DS3232RTC.h>

#include "NormalEffect.h"

// Split into two strips for A/B testing
StarStrip *starStripA, *starStripB;
StarEffect *starEffectA, *starEffectB;

#define STRIP_LENGTH 60
#define STRIP_A_PIN 5
#define STRIP_B_PIN 6

void setup()
{
	setSyncProvider(RTC.get);
	// Serial.begin(9600);
	// if(timeStatus() != timeSet)
	// 	Serial.println("Unable to sync with the RTC");

	randomSeed(42);
	starStripA = new StarStrip(STRIP_LENGTH, STRIP_A_PIN);
	starStripB = new StarStrip(STRIP_LENGTH, STRIP_B_PIN);
	starEffectA = new NormalEffect();
	starEffectB = new NormalEffect();
}

void loop()
{
	starEffectA->Update();
	starEffectB->Update();
	uint32_t start = millis();
	starStripA->Update(starEffectA);
	starStripB->Update(starEffectB);
	uint32_t elapsed = millis() - start;
	if (elapsed < 5) delay(5 - elapsed);
}

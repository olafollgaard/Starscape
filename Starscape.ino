#include "StarStrip.h"
#include <stdio.h>
#include <DS3232RTC.h>

#include "StarEffect.h"

#define STRIP_PIN 5

StarStrip starStripA = StarStrip(STRIP_PIN);
StarEffect starEffect;

void setup()
{
	setSyncProvider(RTC.get);
	// Serial.begin(9600);
	// if(timeStatus() != timeSet)
	// 	Serial.println("Unable to sync with the RTC");

	randomSeed(42);
}

void loop()
{
	starEffect.Update();
	starStripA.Update(&starEffect);
}

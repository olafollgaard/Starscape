#include <Arduino.h>
#include "StarStrip.h"
#include <stdio.h>
#include <DS3232RTC.h>
#include "StatsLcd.h"
#include "StarEffect.h"

#define STRIP_PIN 5

StarStrip starStrip = StarStrip(STRIP_PIN);
StarEffect starEffect;
StatsLcd stats;

void setup()
{
	randomSeed(42);
	stats.Setup();
	stats.lcd.print(F("setSync(RTC):"));
	setSyncProvider(RTC.get);
	stats.lcd.print(timeStatus() == timeSet ? F("ok") : F("failed"));
	delay(3000);
	stats.lcd.clear();
}

void loop()
{
	stats.Update((uint8_t)(starEffect._activePeriod));
	starEffect.Update();
	starStrip.Update(&starEffect);
}

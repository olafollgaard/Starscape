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
	if(stats.Update()) {
		stats.lcd.setCursor(18, 0);
		stats.lcd.print('p');
		stats.lcd.print((uint8_t)(starEffect._activePeriod));

		// stats.lcd.setCursor(0, 3);
		// stats.lcd.print(F("lo:"));
		// stats.lcd.print(starEffect._activeRange.lo.duration16ms);
		// PrintColor(starEffect._activeLimits.lo.color);
		// stats.lcd.print(' ');
		// stats.lcd.print(F("hi:"));
		// stats.lcd.print(starEffect._activeRange.hi.duration16ms);
		// stats.lcd.print(' ');
	}
	starEffect.Update();
	starStrip.Update(&starEffect);
}

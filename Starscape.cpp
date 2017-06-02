#include <Arduino.h>
#include "StarStrip.h"
#include <stdio.h>
#include <DS3232RTC.h>
#include <LiquidCrystal_I2C.h>

#include "StarEffect.h"

#define STRIP_PIN 5

StarStrip starStripA = StarStrip(STRIP_PIN);
StarEffect starEffect;

#define LCD_I2C_Addr 0x27
LiquidCrystal_I2C lcd(LCD_I2C_Addr, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
	lcd.begin(20,4);

	lcd.setCursor(0, 0);
	lcd.print(F("setSync(RTC):"));

	setSyncProvider(RTC.get);
	if(timeStatus() == timeSet)
		lcd.print(F("ok"));
	else
		lcd.print(F("failed"));
	delay(3000);
	lcd.clear();

	randomSeed(42);
}

void PrintTime(time_t t)
{
	lcd.setCursor(0, 0);
	lcd.print(year(t));
	lcd.print('-');
	if (month(t) < 10) lcd.print('0');
	lcd.print(month(t));
	lcd.print('-');
	if (day(t) < 10) lcd.print('0');
	lcd.print(day(t));
	lcd.print(' ');
	if (hour(t) < 10) lcd.print('0');
	lcd.print(hour(t));
	lcd.print(':');
	if (minute(t) < 10) lcd.print('0');
	lcd.print(minute(t));
	lcd.print(' ');
}

void PrintStats(uint16_t fpm, uint16_t ram)
{
	lcd.setCursor(0, 1);
	lcd.print(F("fps:"));
	float fps = fpm / 60.0;
	lcd.print(fps);
	lcd.print(F(" free:"));
	lcd.print(ram);
}

time_t displayTime = 0;
uint16_t fpm = 0;

bool DisplayNeedsUpdate()
{
	time_t _now = now();
	return minute(_now) != minute(displayTime) || hour(_now) != hour(displayTime);
}

int getFreeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void UpdateDisplay()
{
	if (!DisplayNeedsUpdate()) return;
	displayTime = now();
	PrintTime(displayTime);
	PrintStats(fpm, getFreeRam());
	fpm = 0;
}

void loop()
{
	UpdateDisplay();
	starEffect.Update();
	starStripA.Update(&starEffect);
	fpm++;
}

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

#define UNUSED_MEMORY_BYTE_PATTERN 0xA5

void writeStackUsageDetectionPattern()
{
	extern int __heap_start, *__brkval;
	uint8_t *p = (uint8_t*)(__brkval == 0 ? (int) &__heap_start : (int) __brkval);
	while ((uint16_t)p < (uint16_t)&p) *(p++) = UNUSED_MEMORY_BYTE_PATTERN;
}

uint16_t getCurrHeapSize()
{
	extern int __heap_start, *__brkval;
	return (uint16_t)(__brkval == 0 ? 0
		: (uint16_t)__brkval - (uint16_t)&__heap_start);
}

uint16_t getMaxHeapSize()
{
	extern int __heap_start, *__brkval;
	uint8_t *p = (uint8_t*)(__brkval == 0 ? (int) &__heap_start : (int) __brkval);
	while ((uint16_t)p < (uint16_t)&p && *p == UNUSED_MEMORY_BYTE_PATTERN) p++;
	return (uint16_t)p - (uint16_t)&__heap_start;
}

uint16_t getStackPos()
{
	extern int __heap_start;
	uint8_t v;
	return (uint16_t)&v - (uint16_t)&__heap_start;
}

void setup()
{
	writeStackUsageDetectionPattern();
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

time_t displayTime = 0;
uint16_t fpm = 0;

bool DisplayNeedsUpdate()
{
	time_t _now = now();
	return minute(_now) != minute(displayTime) || hour(_now) != hour(displayTime);
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

void PrintStats(uint16_t fpm, uint16_t currHeapSize, uint16_t maxHeapSize,
	uint16_t stackPos)
{
	lcd.setCursor(18, 0);
	lcd.print('p');
	lcd.print((uint8_t)(starEffect._activePeriod));

	lcd.setCursor(0, 1);
	lcd.print(F("hp:"));
	lcd.print(currHeapSize);
	lcd.print(' ');
	lcd.print(F("av:"));
	lcd.print(maxHeapSize - currHeapSize);
	lcd.print(' ');
	lcd.print(F("so:"));
	lcd.print(stackPos - maxHeapSize);
	lcd.print(' ');

	lcd.setCursor(0, 3);
	lcd.print(F("fps:"));
	float fps = fpm / 60.0;
	lcd.print(fps);
	lcd.print(' ');
}

void UpdateDisplay()
{
	displayTime = now();
	uint32_t updateStart = micros();

	PrintTime(displayTime);
	PrintStats(fpm, getCurrHeapSize(), getMaxHeapSize(), getStackPos());
	fpm = 0;

	lcd.print(F("dus:"));
	lcd.print(micros() - updateStart);
	lcd.print(' ');
}

void loop()
{
	if (DisplayNeedsUpdate()) UpdateDisplay();
	starEffect.Update();
	starStripA.Update(&starEffect);
	fpm++;
}
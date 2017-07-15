#include "StatsLcd.h"

#define LCD_I2C_Addr 0x27
#define UNUSED_MEMORY_BYTE_PATTERN 0xA5
#define SECONDS_PER_UPDATE 20

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

// StatsLcd

StatsLcd::StatsLcd() : lcd(LCD_I2C_Addr, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE)
{
	displayTime = 0;
	frameCounter = 0;
}

void StatsLcd::Setup()
{
	writeStackUsageDetectionPattern();
	lcd.begin(20,4);
	lcd.setCursor(0, 0);
}

bool StatsLcd::Update()
{
	if (IsUpdateNeeded()) {
		displayTime = now();
		PrintTime(displayTime);
		PrintStats(getCurrHeapSize(), getMaxHeapSize(), getStackPos());
		frameCounter = 1;
		return true;
	}
	frameCounter++;
	return false;
}

bool StatsLcd::IsUpdateNeeded()
{
	if (displayTime == 0) return true;
	time_t _now = now();
	if (second(_now) % SECONDS_PER_UPDATE != 0) return false;
	return second(_now) != second(displayTime)
		|| minute(_now) != minute(displayTime)
		|| hour(_now) != hour(displayTime);
}

void StatsLcd::PrintTime(time_t t)
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

void StatsLcd::PrintColor(uint32_t color)
{
	lcd.print((uint8_t)(color >> 16), HEX);
	lcd.print((uint16_t)color, HEX);
}

void StatsLcd::PrintStats(uint16_t currHeapSize, uint16_t maxHeapSize, uint16_t stackPos)
{
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

	lcd.setCursor(0, 2);
	lcd.print(F("fps("));
	lcd.print((int)SECONDS_PER_UPDATE);
	lcd.print(F("):"));
	float fps = frameCounter * 1.0 / SECONDS_PER_UPDATE;
	lcd.print(fps);
	lcd.print(' ');
}
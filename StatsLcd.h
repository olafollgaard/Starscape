#ifndef _STATSLCD_H
#define _STATSLCD_H

#include <LiquidCrystal_I2C.h>
#include <Time.h>

class StatsLcd {
private:
public:
	LiquidCrystal_I2C lcd;
	StatsLcd();
	void Setup();
	void Update(uint8_t activePeriod);
private:
	time_t displayTime;
	uint16_t frameCounter;
	bool IsUpdateNeeded();
	void PrintTime(time_t t);
	void PrintColor(uint32_t color);
	void PrintStats(uint8_t activePeriod, uint16_t currHeapSize, uint16_t maxHeapSize, uint16_t stackPos);
};

#endif
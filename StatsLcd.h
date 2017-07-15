#ifndef _STATSLCD_H
#define _STATSLCD_H

#include <LiquidCrystal_I2C.h>
#include <Time.h>

class StatsLcd {
public:
	LiquidCrystal_I2C lcd;
	StatsLcd();
	void Setup();
	bool Update();

	void PrintTime(time_t t);
	void PrintColor(uint32_t color);
private:
	time_t displayTime;
	uint16_t frameCounter;
	bool IsUpdateNeeded();
	void PrintStats(uint16_t currHeapSize, uint16_t maxHeapSize, uint16_t stackPos);
};

#endif
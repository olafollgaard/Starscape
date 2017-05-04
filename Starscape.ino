#include "StarStrip.h"
#include <stdio.h>

StarStrip *starStrip;

void setup()
{
	randomSeed(42);
	starStrip = new StarStrip(STARSTRIP_LENGTH, STARSTRIP_PIN);
}

void loop()
{
	starStrip->Update();
	delay(5);
}

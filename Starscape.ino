#include "StarStrip.h"
#include <stdio.h>

StarStrip *starStrip = new StarStrip();

void setup()
{
	randomSeed(42);
}

void loop()
{
	starStrip->Update();
	delay(5);
}

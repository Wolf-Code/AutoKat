#include "Scale.h"
#include <TimerHelper.h>

HX711 Scale::scale;
long Scale::lastMeasure;

// GPIO0
#define DOUT 3

// GPIO12
#define CLK 6

#define OFFSET 55590;
#define DIVIDER 976;

void Scale::initialize()
{
	Scale::scale.begin(DOUT, CLK);
	
	TimerHelper::startTimer(2000, []() {
		if (scale.wait_ready_timeout(1000))
		{
			const long measured =  Scale::scale.read_average(5);
			const long correctedMeasured = measured - OFFSET;
			const long weightInGrams = correctedMeasured / DIVIDER;
			Scale::lastMeasure = weightInGrams;
		}

		return false;
	},	true);
}

long Scale::getWeightInGrams()
{
	return Scale::lastMeasure;
}
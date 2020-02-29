#include "Timer.h"
#include <Arduino.h>
#include <TimerHelper.h>

Timer::Timer() : start(0), index(0), milliseconds(0), callback(nullptr)
{
}

Timer::Timer(const unsigned int &index, const unsigned int &milliseconds, TimerCallback callback) : index(index), milliseconds(milliseconds), callback(callback)
{
	start = millis();
}

void Timer::validate()
{
	const unsigned long now = millis();
	if (now - start >= milliseconds)
	{
		start = now;
		const bool shouldStop = callback();

		if (shouldStop)
		{
			TimerHelper::stopTimer(*this);
		}
	}
}

unsigned int Timer::getIndex()
{
	return index;
}
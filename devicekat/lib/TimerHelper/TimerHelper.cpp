#include "TimerHelper.h"
#include <Logger.h>

#define timerMax 20

unsigned int TimerHelper::timerId;
Timer TimerHelper::timers[timerMax];
bool TimerHelper::freeTimers[timerMax];

void TimerHelper::initialize()
{
	for (unsigned int i = 0; i < timerMax; i++)
	{
		freeTimers[i] = true;
	}
}

void TimerHelper::loop()
{
	for (unsigned int i = 0; i < timerMax; i++)
	{
		if (freeTimers[i])
		{
			continue;
		}

		timers[i].validate();
	}
}

Timer TimerHelper::startTimer(unsigned int milliseconds, TimerCallback callback, bool startImmediately)
{
	const unsigned int freeIndex = findFreeTimerIndex();
	freeTimers[freeIndex] = false;

	const Timer timer(freeIndex, milliseconds, callback);
	timers[freeIndex] = timer;

	if (startImmediately)
	{
		timers[freeIndex].validate();
	}

	return timer;
}

void TimerHelper::stopTimer(Timer &timer)
{
	const unsigned int index = timer.getIndex();
	freeTimers[index] = true;
}

unsigned int TimerHelper::findFreeTimerIndex()
{
	for (unsigned int i = 0; i < timerMax; i++)
	{
		if (freeTimers[i])
		{
			return i;
		}
	}

	Logger::errorLine("No free timer found.");
	return timerMax + 1;
}
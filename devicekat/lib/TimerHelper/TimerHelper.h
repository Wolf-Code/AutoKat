#ifndef TimerHelper_h
#define TimerHelper_h

#include "Timer.h"
#include <Arduino.h>

class TimerHelper
{
	public:
		static Timer startTimer(unsigned int milliseconds, TimerCallback callback);
		static void stopTimer(Timer &timer);
		static void loop();
		static void initialize();
	private:

		static unsigned int timerId;
		static Timer timers[];
		static bool freeTimers[];
		static unsigned int findFreeTimerIndex();
};

#endif
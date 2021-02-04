#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

typedef bool (* TimerCallback) ();

class Timer
{
public:
	Timer();
	Timer(const unsigned int &index, const unsigned int &milliseconds, TimerCallback callback);
	void validate();
	unsigned int getIndex();

private:
	long unsigned int start;
	unsigned int index;
	unsigned int milliseconds;
	TimerCallback callback;
};

#endif
#include <Arduino.h>
#include <AutoKat.h>
#include <Logger.h>
#include <TimerHelper.h>
#include <Framework.h>
#include <Feeder.h>

void setup()
{
	Framework::initialize(AutoKat::initialize);
}

void loop()
{
	Framework::loop(AutoKat::loop);
}
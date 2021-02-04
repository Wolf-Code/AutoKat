#include <Arduino.h>
#include <AutoKat.h>
#include <Logger.h>
#include <TimerHelper.h>
#include <Framework.h>
#include <Feeder.h>
#include <StorageHelper.h>
#include <Preferences.h>
Preferences preferences;

void setup()
{
	Serial.begin(9600);
	StorageHelper::initialize(preferences);

	Framework::initialize(AutoKat::initialize);
}

void loop()
{
	// Framework::loop(AutoKat::loop);
}
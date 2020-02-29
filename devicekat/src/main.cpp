#include <Arduino.h>
#include <WifiAccess.h>
#include <AutoKat.h>
#include <Logger.h>
#include <Framework.h>

void setup()
{
	Framework::initialize(AutoKat::initialize);
}

void loop()
{
	Framework::loop(AutoKat::loop);
}
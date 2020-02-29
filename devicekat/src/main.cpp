#include <Arduino.h>
#include <WifiAccess.h>
#include <AutoKat.h>
#include <Logger.h>
#include <Framework.h>

AutoKat autoKat;

void setup()
{
	Framework::initialize();

	if (Framework::canRunMainApplication())
	{
		const String macAddress = WifiAccess::getMacAddress();
		Logger::writeLine("Registering device with mac address " + macAddress);
		autoKat.registerDevice(macAddress);
	}
}

void loop()
{
	Framework::loop();
	if (Framework::canRunMainApplication())
	{
	}
}
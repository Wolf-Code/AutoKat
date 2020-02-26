#include <Arduino.h>
#include <WifiAccess.h>
#include <AutoKat.h>
#include <Logger.h>
#include <ConfigurationServer.h>
#include <RequestsHelper.h>

AutoKat autoKat;
ConfigurationServer configServer;

void setup() {
	WifiAccess::connect("BimBamBommel", "WatEenEllende");
	RequestsHelper::initialize("http://192.168.1.61:8080");
	Logger::initialize();
	configServer.start();

	const String macAddress = WifiAccess::getMacAddress();
	Logger::writeLine("Registering device with mac address " + macAddress);
	autoKat.registerDevice(macAddress);
}

void loop() {
	if(!WifiAccess::isConnected())
	{
		return;
	}
}
#include <Arduino.h>
#include <WifiAccess.h>
#include <AutoKat.h>
#include <Logger.h>
#include <ConfigurationServer.h>

Logger logger;
WifiAccess wifi("BimBamBommel", "WatEenEllende");
AutoKat autoKat("http://192.168.1.61:8080");
ConfigurationServer configServer;

void setup() {
	delay(10000);
	logger.waitForInput();
	logger.writeLine("Connecting wifi");
	wifi.connect();
	configServer.start();

	const String macAddress = wifi.getMacAddress();
	logger.writeLine("Registering device with mac address " + macAddress);
	autoKat.registerDevice(macAddress);
}

void loop() {
	if(!wifi.isConnected())
	{
		return;
	}


	delay(1000);
}
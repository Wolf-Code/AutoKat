#include <Arduino.h>
#include <WifiAccess.h>
#include <AutoKat.h>
#include <Logger.h>

Logger logger;
AutoKat autoKat("http://192.168.1.61:8080");
WifiAccess wifi("BimBamBommel", "WatEenEllende");

void setup() {
	delay(10000);
	logger.waitForInput();
	logger.writeLine("Connecting wifi");
	wifi.connect();

}

void loop() {
	if(!wifi.isConnected())
	{
		return;
	}

	const String macAddress = wifi.getMacAddress();
	logger.writeLine("Registering device with mac address " + macAddress);
	autoKat.registerDevice(macAddress);
	delay(1000);
}
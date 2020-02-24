#include <Arduino.h>
#include <WifiAccess.h>
#include <AutoKat.h>

AutoKat autoKat("localhost:8080");
WifiAccess wifi("BimBamBommel", "WatEenEllende");

void setup() {
	wifi.connect();
	autoKat.registerDevice(wifi.getMacAddress());
}

void loop() {
	if(!wifi.isConnected())
	{
		return;
	}
}
#include "WifiAccess.h"
#include <ESP8266WiFi.h>

String WifiAccess::macAddress;

String macToStr(const uint8_t *mac)
{
	String result;
	for (int i = 0; i < 6; ++i)
	{
		result += String(mac[i], 16);
		if (i < 5)
			result += ':';
	}
	return result;
}

String createMacAddressString()
{
	String clientMac = "";
	unsigned char mac[6];
	WiFi.macAddress(mac);
	clientMac += macToStr(mac);

	return clientMac;
}

void WifiAccess::connect(String ssid, String password)
{
	WiFi.begin(ssid, password);

	while (!WifiAccess::isConnected())
	{
		delay(500);
	}

	WifiAccess::macAddress = createMacAddressString();
}

bool WifiAccess::isConnected()
{
	return WiFi.status() == WL_CONNECTED;
}


String WifiAccess::getMacAddress()
{
	return WifiAccess::macAddress;
}
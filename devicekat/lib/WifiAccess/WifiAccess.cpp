#include "WifiAccess.h"
#include <ESP8266WiFi.h>

WifiAccess::WifiAccess(String ssid, String password)
{
	this->ssid = ssid;
	this->password = password;
}

void WifiAccess::connect()
{
	WiFi.begin(this->ssid, this->password);
	
	while (!this->isConnected())
	{
		delay(1000);
	}

	this->logger.debugLine("Connected to wifi at ip: " + WiFi.localIP().toString());
}

bool WifiAccess::isConnected()
{
	return WiFi.status() == WL_CONNECTED;
}

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

String WifiAccess::getMacAddress()
{
	String clientMac = "";
	unsigned char mac[6];
	WiFi.macAddress(mac);
	clientMac += macToStr(mac);

	return clientMac;
}
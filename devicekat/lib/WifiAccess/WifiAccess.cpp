#include "WifiAccess.h"
#include <ESP8266WiFi.h>

String WifiAccess::macAddress;
bool WifiAccess::isAP;

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

bool WifiAccess::connect(String ssid, String password)
{
	WiFi.begin(ssid, password);

	int attempts = 0;
	while (!WifiAccess::isConnected() && WiFi.status() != WL_CONNECT_FAILED)
	{
		if(attempts > 20)
		{
			return false;
		}
		delay(500);
		attempts++;
	}

	if(WiFi.status() == WL_CONNECT_FAILED)
	{
		return false;
	}

	isAP = false;
	WifiAccess::macAddress = createMacAddressString();
	return true;
}

void WifiAccess::startAsSoftAP()
{
	if (WiFi.softAP("AutoKat", "AutoKat123"))
	{
		isAP = true;
		Serial.println("AP started");
		Serial.println(WiFi.softAPIP());
	}
	else
	{
		Serial.println("AP setup failed");
	}
}

bool WifiAccess::isConnected()
{
	return WiFi.status() == WL_CONNECTED;
}

String WifiAccess::getMacAddress()
{
	return WifiAccess::macAddress;
}

bool WifiAccess::isSoftAP()
{
	return isAP;
}
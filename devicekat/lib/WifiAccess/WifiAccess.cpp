#include "WifiAccess.h"
#include <WiFi.h>
#include <Logger.h>
#include <StorageHelper.h>
#include <StorageData.h>

String WifiAccess::macAddress;
bool WifiAccess::isAP;
unsigned int WifiAccess::networks;

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

bool WifiAccess::connect(const String &ssid, const String &password)
{
	WiFi.begin(ssid.c_str(), password.c_str());

	int attempts = 0;
	while (!WifiAccess::isConnected() && WiFi.status() != WL_CONNECT_FAILED)
	{
		if (attempts > 20)
		{
			return false;
		}
		delay(500);
		attempts++;
	}

	if (WiFi.status() == WL_CONNECT_FAILED)
	{
		return false;
	}

	isAP = false;
	WifiAccess::macAddress = createMacAddressString();
	Serial.println(WiFi.localIP().toString());
	return true;
}

bool WifiAccess::connect()
{
	const StorageData data = StorageHelper::getStorageData();
	return WifiAccess::connect(data.wifiSSID, data.wifiPassword);
}

void WifiAccess::disconnect()
{
	WiFi.disconnect();
}

void WifiAccess::startAsSoftAP()
{
	if (WiFi.softAP("AutoKat", "AutoKat123"))
	{
		isAP = true;
		Serial.println(F("AP started"));
		Serial.println(WiFi.softAPIP());
	}
	else
	{
		Serial.println(F("AP setup failed"));
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

IPAddress WifiAccess::getSoftApIp()
{
	return WiFi.softAPIP();
}

bool WifiAccess::isSoftAP()
{
	return isAP;
}

void WifiAccess::stopSoftAP()
{
	if (WiFi.softAPdisconnect(true))
	{
		Logger::debugLine("Disabled AP");
	}
	else
	{
		Logger::debugLine("Failed disabling AP");
	}
}

void WifiAccess::scanNetworks()
{
	networks = WiFi.scanNetworks();
}

unsigned int WifiAccess::getNetworksCount()
{
	return networks;
}

WifiNetwork WifiAccess::getWifiNetwork(unsigned int &index)
{
	const String name = WiFi.SSID(index);
	const int strength = WiFi.RSSI(index);

	return WifiNetwork(name, strength);
}

void WifiAccess::getWifiNetworks(unsigned int &numberOfNetworks, WifiNetwork *networks)
{
	for(unsigned int i = 0; i < numberOfNetworks; ++i)
	{
		networks[i] = getWifiNetwork(i);
	}
}
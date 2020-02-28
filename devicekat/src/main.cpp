#include <Arduino.h>
#include <WifiAccess.h>
#include <AutoKat.h>
#include <Logger.h>
#include <ConfigurationServer.h>
#include <RequestsHelper.h>
#include <OTAHelper.h>
#include <StorageHelper.h>
#include <StorageData.h>

AutoKat autoKat;

void setup()
{
	StorageHelper::initialize();
	WifiAccess::connect("BimBamBommel", "WatEenEllende");
	RequestsHelper::initialize("http://192.168.1.61:8080");
	Logger::initialize();
	ConfigurationServer::start();
	OTAHelper::initialize();

	if (!SPIFFS.begin())
	{
		Logger::errorLine("An Error has occurred while mounting SPIFFS");
	}

	const StorageData data = StorageHelper::getStorageData();
	Logger::debugLine("server: " + data.serverUrl);
	Logger::debugLine("ssid: " + data.wifiSSID);
	Logger::debugLine("password: " + data.wifiPassword);

	const String macAddress = WifiAccess::getMacAddress();
	Logger::writeLine("Registering device with mac address " + macAddress);
	autoKat.registerDevice(macAddress);
}

void loop()
{
	if (!WifiAccess::isConnected())
	{
		return;
	}

	OTAHelper::handle();
}
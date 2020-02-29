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

void startAsAP()
{
	Serial.println("Starting as AP");
	WifiAccess::startAsSoftAP();
	ConfigurationServer::start();
	if (!SPIFFS.begin())
	{
		Serial.println("An Error has occurred while mounting SPIFFS");
	}
}

void startNormally()
{
	const StorageData data = StorageHelper::getStorageData();
	WifiAccess::connect(data.wifiSSID, data.wifiPassword);
	RequestsHelper::initialize(data.serverUrl);
	Logger::initialize();
	OTAHelper::initialize();
	ConfigurationServer::start();

	if (!SPIFFS.begin())
	{
		Logger::errorLine("An Error has occurred while mounting SPIFFS");
	}

	const String macAddress = WifiAccess::getMacAddress();
	Logger::writeLine("Registering device with mac address " + macAddress);
	autoKat.registerDevice(macAddress);
}

void setup()
{
	Serial.begin(115200);
	StorageHelper::initialize();
	// if (!StorageHelper::hasDataBeenWritten())
	// {
	// 	startAsAP();
	// 	return;
	// }

	startNormally();
}

void loop()
{
	OTAHelper::handle();

	if (!WifiAccess::isConnected())
	{
		return;
	}
}
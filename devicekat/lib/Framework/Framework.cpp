#include "Framework.h"
#include <Arduino.h>
#include <ConfigurationServer.h>
#include <WifiAccess.h>
#include <Logger.h>
#include <DeviceHelper.h>
#include <OTAHelper.h>
#include <StorageHelper.h>
#include <StorageData.h>
#include <RequestsHelper.h>

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
	if(!WifiAccess::connect(data.wifiSSID, data.wifiPassword))
	{
		Serial.println("Wifi connect failed, starting as AP");
		startAsAP();
		return;
	}

	RequestsHelper::initialize(data.serverUrl);
	Logger::initialize();
	OTAHelper::initialize();
	ConfigurationServer::start();

	if (!SPIFFS.begin())
	{
		Logger::errorLine("An Error has occurred while mounting SPIFFS");
	}
}

void Framework::initialize()
{
	Serial.begin(115200);
	StorageHelper::initialize();
	if (!StorageHelper::hasDataBeenWritten())
	{
		startAsAP();
		return;
	}

	startNormally();
}

void Framework::loop()
{
	OTAHelper::loop();
	DeviceHelper::loop();
	ConfigurationServer::loop();

	if (!WifiAccess::isConnected())
	{
		return;
	}
}

bool Framework::canRunMainApplication()
{
	return !WifiAccess::isSoftAP();
}
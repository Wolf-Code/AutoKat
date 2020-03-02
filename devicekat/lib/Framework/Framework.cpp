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
#include <TimerHelper.h>

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
	if (!WifiAccess::connect(data.wifiSSID, data.wifiPassword))
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

void Framework::initialize(FrameworkInitializeCallback callback)
{
	Serial.begin(115200);
	StorageHelper::initialize();
	TimerHelper::initialize();
	WiFi.mode(WIFI_STA);
	WifiAccess::scanNetworks();
	TimerHelper::startTimer(30000, []() {
		WifiAccess::scanNetworks();
		return false;
	});

	if (!StorageHelper::hasDataBeenWritten())
	{
		startAsAP();
		return;
	}

	startNormally();
	callback();
}

void Framework::loop(FrameworkLoopCallback callback)
{
	OTAHelper::loop();
	DeviceHelper::loop();
	ConfigurationServer::loop();
	TimerHelper::loop();

	if (!WifiAccess::isConnected())
	{
		return;
	}

	callback();
}

bool Framework::canRunMainApplication()
{
	return !WifiAccess::isSoftAP();
}
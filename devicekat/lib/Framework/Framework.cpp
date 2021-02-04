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
#include <Feeder.h>
#include <Scale.h>
#include <Screen.h>

void startAsAP()
{
	Serial.println("Starting as AP");
	WifiAccess::startAsSoftAP();
	ConfigurationServer::start();
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
	Screen::initialize();
}

void Framework::initialize(FrameworkInitializeCallback callback)
{
	Serial.begin(9600);
	Serial.println("Initializing");

	TimerHelper::initialize();
	WiFi.mode(WIFI_STA);
	WifiAccess::scanNetworks();
	TimerHelper::startTimer(30000, []() {
		WifiAccess::scanNetworks();
		return false;
	}, true);

	Feeder::initialize();
	// Scale::initialize();

	if (!StorageHelper::hasDataBeenWritten())
	{
		Serial.println("Starting as access point");
		startAsAP();
		return;
	}
	Logger::debugLine("Starting normally");

	startNormally();
	callback();
}

void Framework::loop(FrameworkLoopCallback callback)
{
	OTAHelper::loop();
	DeviceHelper::loop();
	ConfigurationServer::loop();
	TimerHelper::loop();
	Feeder::loop();

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
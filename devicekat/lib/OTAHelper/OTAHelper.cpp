#include <Logger.h>
#include <ArduinoOTA.h>
#include "OTAHelper.h"

int OTAHelper::lastPercentage;

void OTAHelper::initialize()
{
	lastPercentage = 0;
	ArduinoOTA.onStart([]() {
		Logger::writeLine("Starting OTA update");
	});

	ArduinoOTA.onEnd([]() {
		OTAHelper::lastPercentage = 0;
		Logger::writeLine("Finished OTA update, restarting");
	});

	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		const float percentage = (progress / (total / 100));
		const int percentageInt = percentage;
		if (percentageInt % 10 == 0 && percentageInt != OTAHelper::lastPercentage)
		{
			OTAHelper::lastPercentage = percentageInt;
			Logger::writeLine("OTA Progress: " + String(percentage));
		}
	});

	ArduinoOTA.onError([](ota_error_t error) {
		OTAHelper::lastPercentage = 0;
		Logger::writeLine("Error: " + error);
		if (error == OTA_AUTH_ERROR)
			Logger::writeLine("Auth Failed");
		else if (error == OTA_BEGIN_ERROR)
			Logger::writeLine("Begin Failed");
		else if (error == OTA_CONNECT_ERROR)
			Logger::writeLine("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR)
			Logger::writeLine("Receive Failed");
		else if (error == OTA_END_ERROR)
			Logger::writeLine("End Failed");
	});

	ArduinoOTA.begin();
}

void OTAHelper::handle()
{
	ArduinoOTA.handle();
}
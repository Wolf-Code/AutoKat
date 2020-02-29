#include <Logger.h>
#include <ArduinoOTA.h>
#include "OTAHelper.h"

int OTAHelper::lastPercentage;

void OTAHelper::initialize()
{
	lastPercentage = 0;
	ArduinoOTA.onStart([]() {
		Logger::infoLine(F("Starting OTA update"));
	});

	ArduinoOTA.onEnd([]() {
		OTAHelper::lastPercentage = 0;
		Logger::infoLine(F("Finished OTA update, restarting"));
	});

	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		const float percentage = (progress / (total / 100));
		const int percentageInt = percentage;
		if (percentageInt % 10 == 0 && percentageInt != OTAHelper::lastPercentage)
		{
			OTAHelper::lastPercentage = percentageInt;
			Logger::infoLine("OTA Progress: " + String(percentage));
		}
	});

	ArduinoOTA.onError([](ota_error_t error) {
		OTAHelper::lastPercentage = 0;
		Logger::infoLine("Error: " + error);
		if (error == OTA_AUTH_ERROR)
			Logger::infoLine(F("Auth Failed"));
		else if (error == OTA_BEGIN_ERROR)
			Logger::infoLine(F("Begin Failed"));
		else if (error == OTA_CONNECT_ERROR)
			Logger::infoLine(F("Connect Failed"));
		else if (error == OTA_RECEIVE_ERROR)
			Logger::infoLine(F("Receive Failed"));
		else if (error == OTA_END_ERROR)
			Logger::infoLine(F("End Failed"));
	});

	ArduinoOTA.begin();
}

void OTAHelper::loop()
{
	ArduinoOTA.handle();
}
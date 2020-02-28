#include <Arduino.h>
#include <WifiAccess.h>
#include <ArduinoJson.h>
#include <RequestsHelper.h>
#include "Logger.h"

String Logger::macAddress;

void Logger::debugLine(String line)
{
	Logger::log(line, "DEBUG");
}

void Logger::writeLine(String line)
{
	Logger::log(line, "INFO");
}

void Logger::errorLine(String line)
{
	Logger::log(line, "ERROR");
}

void Logger::log(String line, String level)
{
	Serial.println(level + ": " + line);

	const int capacity = JSON_OBJECT_SIZE(2) + line.length() + level.length();
	DynamicJsonDocument object(capacity);
	object["message"] = line.c_str();
	object["level"] = level.c_str();

	const String endpoint = "log/" + Logger::macAddress;
	const JsonRequestResult result = RequestsHelper::post(endpoint, object);

	if (!result.requestSuccess)
	{
		const String error = "ERROR: Failed to post to " + endpoint + ": " + result.statusError;
		Serial.println(error);
	}
}

void Logger::waitForInput()
{
	while (Serial.available() == 0)
	{
	}
}

void Logger::initialize()
{
	Serial.begin(115200);
	Logger::macAddress = WifiAccess::getMacAddress();
}
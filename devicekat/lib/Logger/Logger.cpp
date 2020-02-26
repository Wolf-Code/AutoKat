#include <Arduino.h>
#include <WifiAccess.h>
#include "Logger.h"
#include <ArduinoJson.h>
#include <RequestsHelper.h>

Logger::Logger()
{
	Serial.begin(115200);
}

void Logger::debugLine(String line)
{
	this->log(line, "DEBUG");
}

void Logger::writeLine(String line)
{
	this->log(line, "INFO");
}

void Logger::log(String line, String level)
{
	Serial.println(level + ": " + line);

	const int capacity = JSON_OBJECT_SIZE(2) + line.length() + level.length();
	DynamicJsonDocument object(capacity);
	object["message"] = line.c_str();
	object["level"] = level.c_str();

	const String endpoint = "log/" + this->macAddress;
	const JsonRequestResult result = this->requestsHelper.post(endpoint, object);

	if (!result.requestSuccess)
	{
		const String error = "ERROR: Failed to post to " + endpoint + ": " + result.statusError;
		Serial.println(error);
	}
}

void Logger::waitForInput()
{
	Serial.println("Hit a key to start");
	while (Serial.available() == 0)
	{
	}
}

void Logger::initialize()
{
	this->macAddress = WifiAccess::getMacAddress();
}
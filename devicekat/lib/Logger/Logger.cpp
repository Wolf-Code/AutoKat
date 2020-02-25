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
	this->log(line, "DEBUG")
}

void Logger::writeLine(String line)
{
	this->log(line, "INFO");
}

void Logger::log(String line, String level)
{
	Serial.println(level + ": " + line);

 	const int capacity = JSON_OBJECT_SIZE(2) + line.length() + level.length();
	const JsonObject object = this->requestsHelper.createJsonObject(capacity);
	object["message"] = line;
	object["level"] = level;

	this->requestsHelper.post("log/" + this->macAddress, capacity, object);
}

void Logger::waitForInput()
{
	Serial.println ("Hit a key to start");
	while(Serial.available() == 0){}
}

void Logger::initialize()
{
	this->macAddress = WifiAccess::getMacAddress();
}
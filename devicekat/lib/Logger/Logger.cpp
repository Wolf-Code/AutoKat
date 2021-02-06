#include "Logger.h"
#include <Arduino.h>
#include <WifiAccess.h>
#include <ArduinoJson.h>
#include <RequestsHelper.h>

String Logger::macAddress;

void Logger::debugLine(const char* format, ...)
{
	#if DEBUG
		va_list args;
		va_start(args, format);
		char buffer[1024];
		vsprintf(buffer, format, args);
		va_end(args);

		Logger::log(buffer, "DEBUG");
	#endif
}

void Logger::errorLine(const unsigned int bufferSize, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char buffer[bufferSize];
	vsprintf(buffer, format, args);
	va_end(args);

	Logger::log(buffer, "ERROR");
}

void Logger::infoLine(const String &line)
{
	Logger::log(line.c_str(), "INFO");
}

void Logger::errorLine(const String &line)
{
	Logger::log(line.c_str(), "ERROR");
}

void Logger::log(const char* line, const char *level)
{
	const unsigned int bufferSize = strlen(line) + strlen(level) + 4;
	char formatted[bufferSize];
	sprintf(formatted, "[%s]: %s", level, line);	
	Serial.println(formatted);

	if (!WifiAccess::isConnected())
	{
		return;
	}

	// const int capacity = JSON_OBJECT_SIZE(2) + strlen(line) + strlen(level);
	// DynamicJsonDocument object(capacity);
	// object[F("message")] = line;
	// object[F("level")] = level;

	// const String endpoint = "log/" + Logger::macAddress;
	// const JsonRequestResult result = RequestsHelper::post(endpoint, object);

	// if (!result.requestSuccess)
	// {
	// 	char buffer[200];
	// 	sprintf(buffer, "ERROR: Failed to log to %s, %s", endpoint.c_str(), result.statusError.c_str());
	// 	Serial.println(buffer);
	// }
}

void Logger::waitForInput()
{
	while (Serial.available() == 0)
	{
	}
}

void Logger::initialize()
{
	//Serial.begin(115200);
	Logger::macAddress = WifiAccess::getMacAddress();
}
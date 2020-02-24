#include "Logger.h"
#include <Arduino.h>

Logger::Logger()
{
	Serial.begin(115200);
}

void Logger::debugLine(String line)
{
	Serial.println(line);
}

void Logger::writeLine(String line)
{
	Serial.println(line);
}

void Logger::waitForInput()
{
	Serial.println ("Hit a key to start");
	while(Serial.available() == 0){}
}
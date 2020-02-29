#include <Arduino.h>
#include "DeviceHelper.h"

bool DeviceHelper::shouldRestart;

void DeviceHelper::loop()
{
	if (shouldRestart)
	{
		delay(1000);
		ESP.restart();
	}
}

void DeviceHelper::restart()
{
	shouldRestart = true;
}
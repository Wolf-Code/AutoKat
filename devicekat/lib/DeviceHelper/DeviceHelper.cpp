#include "DeviceHelper.h"
#include <Arduino.h>
#include <WifiAccess.h>

bool DeviceHelper::shouldRestart;

void DeviceHelper::loop()
{
	if (shouldRestart)
	{
		if(WifiAccess::isSoftAP())
		{
			WifiAccess::stopSoftAP();
		}
		
		delay(1000);

		ESP.restart();
	}
}

void DeviceHelper::restart()
{
	shouldRestart = true;
}
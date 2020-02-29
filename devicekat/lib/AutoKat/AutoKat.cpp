#include "AutoKat.h"
#include <Logger.h>
#include <JsonRequestResult.h>
#include <RequestsHelper.h>
#include <WifiAccess.h>

String AutoKat::id;
String AutoKat::name;

void AutoKat::registerDevice(String id)
{
	AutoKat::id = id;
	const int capacity = JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(4) + 80;
	const String endpoint = "device/" + id;
	const JsonRequestResult result = RequestsHelper::get(endpoint, capacity);
	
	if (result.requestSuccess && result.deserializeSuccess)
	{
		const DynamicJsonDocument json = *result.document;
		const String name = json["name"].as<String>();

		AutoKat::name = name;
	}
	else
	{
		Logger::debugLine("failed to register device");
		Logger::debugLine(result.statusError);
		Logger::debugLine(result.deserializationError.c_str());
	}
}

void AutoKat::initialize()
{
	const String macAddress = WifiAccess::getMacAddress();
	Logger::writeLine("Registering device with mac address " + macAddress);
	AutoKat::registerDevice(macAddress);
}

void AutoKat::loop()
{

}
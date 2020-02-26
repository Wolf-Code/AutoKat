#include <Logger.h>
#include "AutoKat.h"
#include <JsonRequestResult.h>
#include <RequestsHelper.h>

void AutoKat::registerDevice(String id)
{
	this->id = id;
	const int capacity = JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(4) + 80;
	const String endpoint = "device/" + id;
	const JsonRequestResult result = RequestsHelper::get(endpoint, capacity);
	
	if (result.requestSuccess && result.deserializeSuccess)
	{
		const DynamicJsonDocument json = *result.document;
		const String name = json["name"].as<String>();

		this->name = name;
	}
	else
	{
		Logger::debugLine("failed to register device");
		Logger::debugLine(result.statusError);
		Logger::debugLine(result.deserializationError.c_str());
	}
}
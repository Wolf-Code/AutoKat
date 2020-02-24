#include "AutoKat.h"
#include "JsonRequestResult.h"

AutoKat::AutoKat(String serverUrl)
{
	this->requestsHelper.serverUrl = serverUrl;
}

void AutoKat::registerDevice(String id)
{
	this->id = id;
	const int capacity = JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(4) + 80;
	const String endpoint = "device/" + id;
	const JsonRequestResult result = this->requestsHelper.get(endpoint, capacity);
	if (result.requestSuccess && result.deserializeSuccess)
	{
		this->logger.debugLine("result success");
		const DynamicJsonDocument json = *result.document;
		this->logger.debugLine("retrieved document");
		const String name = json["name"].as<String>();
		this->logger.debugLine("retrieved name " + name);

		this->name = name;
	}
	else
	{
		logger.debugLine("failed to register device");
		logger.debugLine(result.statusError);
		logger.debugLine(result.deserializationError.c_str());
	}
}
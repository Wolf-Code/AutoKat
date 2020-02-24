#include "AutoKat.h"
#include "JsonRequestResult.h"

AutoKat::AutoKat(String serverUrl)
{
	this->requestsHelper.serverUrl = serverUrl;
}

void AutoKat::registerDevice(String id)
{
	this->id = id;
	const int capacity = JSON_OBJECT_SIZE(4);
	const JsonRequestResult result = this->requestsHelper.get("/device/" + id, capacity);
	const DynamicJsonDocument json = *result.document;

	this->name = json["name"].as<String>();
}
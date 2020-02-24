#include <WiFiClient.h>
#include "RequestsHelper.h"

void RequestsHelper::begin(String endPoint)
{
	WiFiClient client;

	this->httpClient.begin(client, this->serverUrl + '/' + endPoint);
}

JsonRequestResult RequestsHelper::get(String endPoint, int bufferSize)
{
	this->begin(endPoint);
	JsonRequestResult result(bufferSize);
	result.status = this->httpClient.GET();

	DynamicJsonDocument doc(bufferSize);
	result.document = &doc;

	if (result.status == 200)
	{
		result.success = true;
		const String json = this->httpClient.getString();
		const DeserializationError deserialized = deserializeJson(*result.document, json);
		result.error = deserialized;
	}

	this->httpClient.end();

	return result;
}
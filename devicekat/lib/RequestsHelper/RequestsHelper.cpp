#include "RequestsHelper.h"

String RequestsHelper::getUrlToEndPoint(String endpoint)
{
	const String url = this->serverUrl + "/" + endpoint;
	return url;
}

JsonRequestResult RequestsHelper::get(String endPoint, int bufferSize)
{
	const String url = this->getUrlToEndPoint(endPoint);

	JsonRequestResult result(bufferSize);

	WiFiClient wifiClient;
	HTTPClient http;

	if (http.begin(wifiClient, url))
	{
		const int status = http.GET();
		Serial.println(status);
		result.status = status;

		if (result.status == HTTP_CODE_OK)
		{
			result.requestSuccess = true;
			const String json = http.getString();

			const DeserializationError deserialized = deserializeJson(*result.document, json);
			result.deserializationError = deserialized;
			result.deserializeSuccess = !deserialized;
		}
		else
		{
			const String error = http.errorToString(status);
			result.statusError = error;
		}

		http.end();

		return result;
	}
}

JsonRequestResult RequestsHelper::post(String endPoint, int bufferSize, JsonObject &object)
{
	const String url = this->getUrlToEndPoint(endPoint);

	JsonRequestResult result(bufferSize);

	WiFiClient wifiClient;
	HTTPClient http;

	if (http.begin(wifiClient, url))
	{
		http.addHeader("Content-Type", "application/json");
		String jsonRequest;
		serializeJson(object, jsonRequest);
		const int status = http.POST(jsonRequest);

		Serial.println(status);
		result.status = status;

		if (result.status == HTTP_CODE_OK)
		{
			result.requestSuccess = true;
			const String json = http.getString();

			const DeserializationError deserialized = deserializeJson(*result.document, json);
			result.deserializationError = deserialized;
			result.deserializeSuccess = !deserialized;
		}
		else
		{
			const String error = http.errorToString(status);
			result.statusError = error;
		}

		http.end();
	}

	return result;
}

JsonObject RequestsHelper::createJsonObject(const size_t capacity)
{
	const StaticJsonDocument<500> doc;
	JsonObject object = doc.to<JsonObject>();

	return object;
}
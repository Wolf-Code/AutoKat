#include "RequestsHelper.h"

String RequestsHelper::serverUrl;

String RequestsHelper::getUrlToEndPoint(String endpoint)
{
	const String url = serverUrl + "/" + endpoint;
	return url;
}

JsonRequestResult RequestsHelper::get(String endPoint, int bufferSize)
{
	const String url = RequestsHelper::getUrlToEndPoint(endPoint);

	JsonRequestResult result(bufferSize);

	WiFiClient wifiClient;
	HTTPClient http;

	if (http.begin(wifiClient, url))
	{
		const int status = http.GET();
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

JsonRequestResult RequestsHelper::post(String endPoint, int bufferSize, JsonDocument payload)
{
	const String url = RequestsHelper::getUrlToEndPoint(endPoint);

	JsonRequestResult result(bufferSize);

	WiFiClient wifiClient;
	HTTPClient http;

	if (http.begin(wifiClient, url))
	{
		http.addHeader("Content-Type", "application/json");
		String jsonRequest;
		serializeJson(payload, jsonRequest);
		const int status = http.POST(jsonRequest);
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

JsonRequestResult RequestsHelper::post(String endPoint, JsonDocument payload)
{
	const String url = RequestsHelper::getUrlToEndPoint(endPoint);

	JsonRequestResult result(0);

	WiFiClient wifiClient;
	HTTPClient http;

	if (http.begin(wifiClient, url))
	{
		http.addHeader("Content-Type", "application/json");
		String jsonRequest;
		serializeJson(payload, jsonRequest);
		const int status = http.POST(jsonRequest);
		result.status = status;

		if (result.status == HTTP_CODE_OK)
		{
			result.requestSuccess = true;
			result.deserializationError = DeserializationError::Ok;
			result.deserializeSuccess = true;
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

void RequestsHelper::initialize(String url)
{
	serverUrl = url;
}
#include "RequestsHelper.h"
#include <HTTPClient.h>
#include <Arduino.h>
#include <Logger.h>
#include <ArduinoJson.h>
#include <StorageHelper.h>

String RequestsHelper::serverUrl;
String RequestsHelper::token;
String RequestsHelper::refreshToken;

String RequestsHelper::getUrlToEndPoint(String endpoint)
{
	const String url = serverUrl + "/" + endpoint;
	
	return url;
}

void RequestsHelper::get(String endPoint, JsonRequestResult &result)
{
	const String url = RequestsHelper::getUrlToEndPoint(endPoint);

	HTTPClient http;

	if (http.begin(url))
	{
		http.addHeader(F("Authorization"), "Bearer " + RequestsHelper::token);
		const int status = http.GET();
		Serial.println(status);
		result.status = status;

		if(result.status == HTTP_CODE_UNAUTHORIZED)
		{
			http.end();
			RequestsHelper::retrieveNewToken();

			return RequestsHelper::get(endPoint, result);
		}

		if (result.status == HTTP_CODE_OK)
		{
			result.requestSuccess = true;
			const String json = http.getString();

			const DeserializationError deserialized = deserializeJson(result.document, json);
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
}

JsonRequestResult RequestsHelper::post(String endPoint, int bufferSize, JsonDocument& payload)
{
	const String url = RequestsHelper::getUrlToEndPoint(endPoint);

	JsonRequestResult result(bufferSize);

	HTTPClient http;

	if (http.begin(url))
	{
		http.addHeader(F("Authorization"), "Bearer " + RequestsHelper::token);
		http.addHeader(F("Content-Type"), F("application/json"));
		String jsonRequest;
		serializeJson(payload, jsonRequest);
		const int status = http.POST(jsonRequest);
		result.status = status;

		if(result.status == HTTP_CODE_UNAUTHORIZED)
		{
			http.end();
			RequestsHelper::retrieveNewToken();

			return RequestsHelper::post(endPoint, bufferSize, payload);
		}

		if (result.status == HTTP_CODE_OK)
		{
			result.requestSuccess = true;
			const String json = http.getString();

			const DeserializationError deserialized = deserializeJson(result.document, json);
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

void RequestsHelper::retrieveNewToken()
{
	const String url = RequestsHelper::getUrlToEndPoint("refresh");

	JsonRequestResult result(384);

	HTTPClient http;

	if (http.begin(url))
	{
		http.addHeader(F("RefreshToken"), RequestsHelper::refreshToken);
		
		const int status = http.GET();
		result.status = status;

		if (result.status == HTTP_CODE_OK)
		{
			const String json = http.getString();
			deserializeJson(result.document, json);
			const String newToken = result.asObject()[F("authenticationData")][F("token")];
			RequestsHelper::token = newToken;
		}
		else
		{
			const String error = http.errorToString(status);
			result.statusError = error;
		}

		http.end();
	}
}

void RequestsHelper::initialize(String url)
{
	serverUrl = url;
	// const StorageData storedData = StorageHelper::getStorageData();
	RequestsHelper::refreshToken = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjZXJ0c2VyaWFsbnVtYmVyIjoiYWJjZCIsIm5iZiI6MTYxMjY0MDY3MSwiZXhwIjoxNjE1MDU5ODcxLCJpYXQiOjE2MTI2NDA2NzF9.NixHFIYmKP-mnH5KwpUM3SwrmzJrO2I2FOukVYwx97o";
}
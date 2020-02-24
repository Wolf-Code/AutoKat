#include "RequestsHelper.h"

JsonRequestResult RequestsHelper::get(String endPoint, int bufferSize)
{
	const String url = this->serverUrl + "/" + endPoint;
	this->logger.debugLine("beginning get request to " + url);

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
			this->logger.debugLine(json);

			const DeserializationError deserialized = deserializeJson(*result.document, json);
			result.deserializationError = deserialized;
			result.deserializeSuccess = !deserialized;
		}
		else
		{
			const String error = http.errorToString(status);
			result.statusError = error;
			logger.debugLine("failed to get: " + error);
		}

		http.end();
	}
	else
	{
		this->logger.debugLine("Failed to begin request");
	}

	return result;
}
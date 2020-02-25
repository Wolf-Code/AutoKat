#ifndef RequestsHelper_h
#define RequestsHelper_h

#include <ESP8266HTTPClient.h>
#include <JsonRequestResult.h>
#include <WString.h>
#include <Logger.h>
#include <WiFiClient.h>

class RequestsHelper
{
	public:
		JsonRequestResult get(String endpoint, int bufferSize);
		JsonRequestResult post(String endpoint, int capacity, JsonObject& object);
		JsonObject createJsonObject(const size_t capacity);
		String serverUrl;
	private:
		String getUrlToEndPoint(String endpoint);
};

#endif

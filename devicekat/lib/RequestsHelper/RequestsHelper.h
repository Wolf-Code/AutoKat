#ifndef RequestsHelper_h
#define RequestsHelper_h

#include <ESP8266HTTPClient.h>
#include <JsonRequestResult.h>
#include <WString.h>
#include <WiFiClient.h>

class RequestsHelper
{
	public:
		static JsonRequestResult get(String endpoint, int bufferSize);
		static JsonRequestResult post(String endpoint, int responseCapacity, JsonDocument payload);
		static JsonRequestResult post(String endpoint, JsonDocument payload);
		static void initialize(String serverUrl);
	private:
		static String getUrlToEndPoint(String endpoint);
		static String serverUrl;
};

#endif

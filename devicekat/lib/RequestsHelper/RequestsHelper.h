#ifndef RequestsHelper_h
#define RequestsHelper_h

#include <ESP8266HTTPClient.h>
#include <JsonRequestResult.h>
#include <WString.h>
#include <WiFiClient.h>

class RequestsHelper
{
	public:
		JsonRequestResult get(String endpoint, int bufferSize);
		JsonRequestResult post(String endpoint, int responseCapacity, JsonDocument payload);
		JsonRequestResult post(String endpoint, JsonDocument payload);
		String serverUrl;
	private:
		String getUrlToEndPoint(String endpoint);
};

#endif

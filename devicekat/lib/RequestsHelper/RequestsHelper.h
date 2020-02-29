#ifndef RequestsHelper_h
#define RequestsHelper_h

#include <JsonRequestResult.h>
#include <WString.h>
#include <WiFiClient.h>

class RequestsHelper
{
	public:
		static void get(String endpoint, JsonRequestResult &result);
		static JsonRequestResult post(String endpoint, int responseCapacity, JsonDocument payload);
		static JsonRequestResult post(String endpoint, JsonDocument payload);
		static void initialize(String serverUrl);
	private:
		static String getUrlToEndPoint(String endpoint);
		static String serverUrl;
};

#endif

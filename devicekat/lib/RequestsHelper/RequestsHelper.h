#ifndef RequestsHelper_h
#define RequestsHelper_h

#include <ESP8266HTTPClient.h>
#include <JsonRequestResult.h>
#include <WString.h>

class RequestsHelper
{
	public:
		JsonRequestResult get(String endpoint, int bufferSize);
		String serverUrl;
	private:
		HTTPClient httpClient;
		void begin(String endpoint);
};

#endif

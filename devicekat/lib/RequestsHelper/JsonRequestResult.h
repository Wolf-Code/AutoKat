#ifndef JsonRequestResult_h
#define JsonRequestResult_h
#include <ArduinoJson.h>

class JsonRequestResult
{
	public:
		JsonRequestResult(int capacity);
		~JsonRequestResult();
		DynamicJsonDocument* document;
		DeserializationError error;
		bool success;
		int status;
};

#endif
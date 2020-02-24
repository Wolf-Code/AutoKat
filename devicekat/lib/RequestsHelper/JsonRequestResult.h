#ifndef JsonRequestResult_h
#define JsonRequestResult_h
#include <ArduinoJson.h>

class JsonRequestResult
{
	public:
		JsonRequestResult(int capacity);
		~JsonRequestResult();
		DynamicJsonDocument* document;
		DeserializationError deserializationError;
		String statusError;
		bool requestSuccess;
		bool deserializeSuccess;
		int status;
};

#endif
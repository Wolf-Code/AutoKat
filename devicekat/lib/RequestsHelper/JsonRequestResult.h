#ifndef JsonRequestResult_h
#define JsonRequestResult_h
#include <ArduinoJson.h>

class JsonRequestResult
{
	public:
		JsonRequestResult(const unsigned int capacity);
		JsonObject asObject();
		JsonArray asArray();
		DynamicJsonDocument document;
		DeserializationError deserializationError;
		String statusError;
		bool requestSuccess;
		bool deserializeSuccess;
		int status;
};

#endif
#include "JsonRequestResult.h"

JsonRequestResult::JsonRequestResult(const unsigned int capacity) : document(capacity)
{
	
}

JsonObject JsonRequestResult::asObject()
{
	return this->document.as<JsonObject>();
}

JsonArray JsonRequestResult::asArray()
{
	return this->document.as<JsonArray>();
}
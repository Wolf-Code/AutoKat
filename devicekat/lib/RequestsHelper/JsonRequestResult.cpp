#include "JsonRequestResult.h"

JsonRequestResult::JsonRequestResult(int capacity)
{
	this->document = new DynamicJsonDocument(capacity);
}

JsonRequestResult::~JsonRequestResult()
{
	if(this->document != nullptr)
	{
		delete this->document;
	}
}
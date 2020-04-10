#include "AutoKat.h"
#include <Logger.h>
#include <JsonRequestResult.h>
#include <RequestsHelper.h>
#include <WifiAccess.h>
#include <TimerHelper.h>
#include <Feeder.h>
#include <Scale.h>
#include <Screen.h>

String AutoKat::id;
String AutoKat::name;

void AutoKat::initialize()
{
	const String macAddress = WifiAccess::getMacAddress();
	Logger::infoLine("Registering device with mac address " + macAddress);
	AutoKat::registerDevice(macAddress);

	const unsigned int queryTime = 10 * 60 * 1000;
	TimerHelper::startTimer(queryTime, []() {
		const unsigned int currentAmount = AutoKat::getAmountCurrentlyRequired();

		Logger::debugLine("Current amount: %d", currentAmount);

		return false;
	}, false);

	TimerHelper::startTimer(15000, [](void){
		Feeder::rotate();

		return false;
	}, true);
}

void AutoKat::loop()
{
	const long weight = Scale::getWeightInGrams();
	Screen::clear();
	Screen::writeText(0, 0, "%ld", weight);
	Screen::render();
}

void AutoKat::registerDevice(const String &id)
{
	AutoKat::id = id;
	const int capacity = JSON_ARRAY_SIZE(0) + JSON_OBJECT_SIZE(4) + 80;
	const String endpoint = "device/" + id;

	JsonRequestResult result(capacity);
	RequestsHelper::get(endpoint, result);

	if (result.requestSuccess && result.deserializeSuccess)
	{
		const JsonObject json = result.asObject();
		const String name = json[F("name")];

		AutoKat::name = name;
	}
	else
	{
		const char format[] = "failed to register device: %s";
		const unsigned int bufferSize = strlen(format) + 20;
		Logger::errorLine(bufferSize, format, result.statusError.c_str());
	}
}

unsigned int AutoKat::getAmountCurrentlyRequired()
{
	const int capacity = JSON_OBJECT_SIZE(4) + 11;
	const String endpoint = "food/" + id + "/query";
	JsonRequestResult result(capacity);
	RequestsHelper::get(endpoint, result);

	if (result.requestSuccess && result.deserializeSuccess)
	{
		const JsonObject json = result.asObject();
		const unsigned int amount = json[F("amount")];

		return amount;
	}
	else
	{
		const char format[] = "failed to query food information: %s";
		const unsigned int bufferSize = strlen(format) + 20;
		Logger::errorLine(bufferSize, format, result.statusError.c_str());

		return 0;
	}
}

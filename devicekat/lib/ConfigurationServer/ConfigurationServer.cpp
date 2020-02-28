#include <Logger.h>
#include <StorageHelper.h>
#include <StorageData.h>
#include "ConfigurationServer.h"

AsyncWebServer ConfigurationServer::server(80);

String processor(const String &var)
{
	const StorageData data = StorageHelper::getStorageData();
	if (var == "SERVER_URL")
	{
		return data.serverUrl;
	}

	if (var == "SSID")
	{
		return data.wifiSSID;
	}

	if (var == "PASSWORD")
	{
		return data.wifiPassword;
	}

	return "";
}

void ConfigurationServer::start()
{
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(SPIFFS, "/index.html", "text/html", false, processor);
	});

	server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
		Logger::debugLine("handling /save");

		int params = request->params();
		Serial.printf("%d params sent in\n", params);
		for (int i = 0; i < params; i++)
		{
			AsyncWebParameter *p = request->getParam(i);
			if (p->isFile())
			{
				Serial.printf("_FILE[%s]: %s, size: %u", p->name().c_str(), p->value().c_str(), p->size());
			}
			else if (p->isPost())
			{
				Serial.printf("_POST[%s]: %s", p->name().c_str(), p->value().c_str());
			}
			else
			{
				Serial.printf("_GET[%s]: %s", p->name().c_str(), p->value().c_str());
			}
		}

		StorageData storageData = StorageHelper::getStorageData();

		if (request->hasParam("server", true))
		{
			storageData.serverUrl = request->getParam("server", true)->value();
		}

		if (request->hasParam("ssid", true))
		{
			storageData.wifiSSID = request->getParam("ssid", true)->value();
		}

		if (request->hasParam("password", true))
		{
			storageData.wifiPassword = request->getParam("password", true)->value();
		}

		StorageHelper::saveStorageData(storageData);
		request->redirect("/");
	});

	server.onNotFound([](AsyncWebServerRequest *request) {
		request->send(404, "text/plain", "Die is er niet vriend");
	});

	server.begin();
	Logger::debugLine("Starting configuration server");
}
#include "ConfigurationServer.h"
#include <WifiAccess.h>
#include <Logger.h>
#include <StorageHelper.h>
#include <StorageData.h>
#include <DeviceHelper.h>

AsyncWebServer ConfigurationServer::server(80);
DNSServer ConfigurationServer::dnsServer;
const int dnsPort = 53;

String indexProcessor(const String &var)
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
		request->send(SPIFFS, "/pages/index.html", "text/html", false, indexProcessor);
	});

	server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
		Logger::debugLine("handling /save");

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
		request->send(SPIFFS, "/pages/success.html", "text/html");
		DeviceHelper::restart();
	});

	server.serveStatic("/scripts.js", SPIFFS, "/scripts.js");
	server.serveStatic("/styles.css", SPIFFS, "/styles.css");

	server.onNotFound([](AsyncWebServerRequest *request) {
		request->send(404, "text/plain", "Die is er niet vriend");
	});

	server.begin();
	if (WifiAccess::isSoftAP())
	{
		dnsServer.start(dnsPort, "*", WiFi.softAPIP());
	}
	Logger::debugLine("Starting configuration server");
}

void ConfigurationServer::debugAsyncWebServerRequest(AsyncWebServerRequest *request)
{
	const int params = request->params();
	Serial.printf("%d params sent in\n", params);
	for (int i = 0; i < params; i++)
	{
		AsyncWebParameter *p = request->getParam(i);
		if (p->isFile())
		{
			Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
		}
		else if (p->isPost())
		{
			Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
		}
		else
		{
			Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
		}
	}
}

void ConfigurationServer::loop()
{
	if (WifiAccess::isSoftAP())
	{
		dnsServer.processNextRequest();
	}
}
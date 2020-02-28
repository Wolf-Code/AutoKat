#include "ConfigurationServer.h"

AsyncWebServer ConfigurationServer::server(80);

String processor(const String &var)
{
    if (var == "SERVER_URL")
    {
        return "localhost";
    }

    if (var == "SSID")
    {
        return "ssid";
    }

    if (var == "PASSWORD")
    {
        return "password";
    }

    return "";
}

void ConfigurationServer::start()
{
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("server", true))
        {
        }
    });

    server.begin();
}
#ifndef ConfigurationServer_h
#define ConfigurationServer_h

#include <ESPAsyncWebServer.h>

class ConfigurationServer
{
    public:
        static void start();
    private:
        static AsyncWebServer server;
		static void debugAsyncWebServerRequest(AsyncWebServerRequest* request);
};

#endif
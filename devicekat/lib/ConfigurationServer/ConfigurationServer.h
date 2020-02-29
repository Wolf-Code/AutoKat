#ifndef ConfigurationServer_h
#define ConfigurationServer_h

#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

class ConfigurationServer
{
    public:
        static void start();
        static void loop();
    private:
        static AsyncWebServer server;
		static DNSServer dnsServer;
		static void debugAsyncWebServerRequest(AsyncWebServerRequest* request);
};

#endif
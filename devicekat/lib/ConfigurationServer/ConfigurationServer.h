#ifndef ConfigurationServer_h
#define ConfigurationServer_h

#include <ESPAsyncWebServer.h>

class ConfigurationServer
{
    public:
        void start();
        ~ConfigurationServer();

    private:
        AsyncWebServer* server;
};

#endif
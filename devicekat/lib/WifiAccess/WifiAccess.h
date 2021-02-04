#ifndef WifiAccess_h
#define WifiAccess_h

#include <WString.h>
#include <WifiNetwork.h>
#include <WiFi.h>

class WifiAccess
{
	public:
		static bool isSoftAP();
		static bool isConnected();
		static bool connect(const String &ssid, const String &password);
		static bool connect();
		static void disconnect();
		static void startAsSoftAP();
		static void stopSoftAP();
		static IPAddress getSoftApIp();
		static String getMacAddress();
		static void scanNetworks();
		static unsigned int getNetworksCount();
		static WifiNetwork getWifiNetwork(unsigned int &index);
		static void getWifiNetworks(unsigned int &numberOfNetworks, WifiNetwork *networks);
	private: 
		static String macAddress;
		static bool isAP;
		static unsigned int networks;
};

#endif
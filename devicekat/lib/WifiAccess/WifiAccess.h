#ifndef WifiAccess_h
#define WifiAccess_h

#include <WString.h>

class WifiAccess
{
	public:
		static bool isSoftAP();
		static bool isConnected();
		static bool connect(const String &ssid, const String &password);
		static void startAsSoftAP();
		static void stopSoftAP();
		static String getMacAddress();
	private: 
		static String macAddress;
		static bool isAP;
};

#endif
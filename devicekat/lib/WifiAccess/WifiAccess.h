#ifndef WifiAccess_h
#define WifiAccess_h

#include <WString.h>

class WifiAccess
{
	public:
		static bool isSoftAP();
		static bool isConnected();
		static bool connect(String ssid, String password);
		static void startAsSoftAP();
		static String getMacAddress();
	private: 
		static String macAddress;
		static bool isAP;
};

#endif
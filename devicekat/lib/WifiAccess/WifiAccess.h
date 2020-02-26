#ifndef WifiAccess_h
#define WifiAccess_h

#include <WString.h>

class WifiAccess
{
	public:
		static bool isConnected();
		static void connect(String ssid, String password);
		static String getMacAddress();
	private: 
		static String macAddress;
};

#endif
#ifndef WifiAccess_h
#define WifiAccess_h

#include <WString.h>

class WifiAccess
{
	public:
		WifiAccess(String ssid, String password);
		bool isConnected();
		void connect();
		String getMacAddress();
	private: 
		String ssid;
		String password;
};

#endif
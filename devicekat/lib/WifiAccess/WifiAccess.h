#ifndef WifiAccess_h
#define WifiAccess_h

#include <WString.h>
#include <Logger.h>

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
		Logger logger;
};

#endif
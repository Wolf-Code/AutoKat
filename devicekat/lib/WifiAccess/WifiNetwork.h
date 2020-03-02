#ifndef WifiNetwork_h
#define WifiNetwork_h

#include <WString.h>

struct WifiNetwork
{
public:
	WifiNetwork(String name, int strength) : name(name), strength(strength) {}
	String name;
	int strength;
};

#endif
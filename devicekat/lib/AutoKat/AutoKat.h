#ifndef AutoKat_h
#define AutoKat_h

#include <WString.h>

class AutoKat
{
	public:
		static void registerDevice(const String& id);
		static void initialize();
		static void loop();
		static unsigned int getAmountCurrentlyRequired();
	private:
		static String id;
		static String name;
};

#endif
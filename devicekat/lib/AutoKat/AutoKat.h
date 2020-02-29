#ifndef AutoKat_h
#define AutoKat_h

#include <WString.h>

class AutoKat
{
	public:
		static void registerDevice(String id);
		static void initialize();
		static void loop();
	private:
		static String id;
		static String name;
};

#endif
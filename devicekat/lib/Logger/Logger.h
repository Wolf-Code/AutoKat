#ifndef Logger_h
#define Logger_h

#include <WString.h>

class Logger
{
	public:
		static void writeLine(String line);
		static void debugLine(String line);
		static void waitForInput();
		static void initialize();
	private:
		static String macAddress;
		static void log(String line, String level);
};

#endif
#ifndef Logger_h
#define Logger_h

#include <WString.h>

class Logger
{
	public:
		static void errorLine(const String &line);
		static void errorLine(const unsigned int bufferSize, const char *format, ...);
		static void infoLine(const String &line);
		static void debugLine(const char *format, ...);
		static void waitForInput();
		static void initialize();
	private:
		static String macAddress;
		static void log(const char* line, const char* level);
};

#endif
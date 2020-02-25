#ifndef Logger_h
#define Logger_h

#include <WString.h>
#include <RequestsHelper.h>

class Logger
{
	public:
		Logger();
		void writeLine(String line);
		void debugLine(String line);
		void waitForInput();
		void initialize();
	private:
		RequestsHelper requestsHelper;
		String macAddress;
		void log(String line, String level);
};

#endif
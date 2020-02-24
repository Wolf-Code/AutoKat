#ifndef Logger_h
#define Logger_h

#include <WString.h>

class Logger
{
	public:
		Logger();
		void writeLine(String line);
		void debugLine(String line);
		void waitForInput();
};

#endif
#ifndef AutoKat_h
#define AutoKat_h

#include <WString.h>

class AutoKat
{
	public:
		void registerDevice(String id);
	private:
		String id;
		String name;
};

#endif
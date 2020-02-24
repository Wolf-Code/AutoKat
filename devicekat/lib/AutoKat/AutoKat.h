#ifndef AutoKat_h
#define AutoKat_h

#include <WString.h>
#include <RequestsHelper.h>

class AutoKat
{
	public:
		AutoKat(String serverUrl);
		void registerDevice(String id);
	private:
		String id;
		String name;
		RequestsHelper requestsHelper;
};

#endif
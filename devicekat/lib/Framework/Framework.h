#ifndef Framework_h
#define Framework_h

#include <Arduino.h>

typedef std::function<void(void)> FrameworkInitializeCallback;
typedef std::function<void(void)> FrameworkLoopCallback;

class Framework
{
	public:
		static void initialize(FrameworkInitializeCallback callback);
		static void loop(FrameworkLoopCallback callback);
		static bool canRunMainApplication();
};

#endif
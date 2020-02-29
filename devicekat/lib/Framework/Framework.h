#ifndef Framework_h
#define Framework_h

class Framework
{
	public:
		static void initialize(void (*pApplicationInitializeFunc)(void));
		static void loop(void (*pApplicationLoopFunc)(void));
		static bool canRunMainApplication();
};

#endif
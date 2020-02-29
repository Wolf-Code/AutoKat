#ifndef DeviceHelper_h
#define DeviceHelper_h

class DeviceHelper
{
	public:
		static void loop();
		static void restart();
	private:
		static bool shouldRestart;
};

#endif
#ifndef OTAHelper_h
#define OTAHelper_h

class OTAHelper
{
	public:
		static void initialize();
		static void loop();
	private: 
		static int lastPercentage;
};

#endif
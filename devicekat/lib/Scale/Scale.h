#ifndef Scale_h
#define Scale_h
#include <HX711.h>

class Scale 
{
	public:
		static void initialize(void);
		static long getWeightInGrams(void);

	private:
		static HX711 scale;
		static long lastMeasure;
};

#endif
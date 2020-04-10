#ifndef FEEDER_h
#define FEEDER_h
#include <AccelStepper.h>

class Feeder
{
	public:
		static void rotate(void);
		static void loop(void);
		static void initialize(void);
	private:
		static AccelStepper stepper;
};

#endif
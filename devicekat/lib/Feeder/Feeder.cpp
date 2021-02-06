#include "Feeder.h"
#include <AccelStepper.h>

#define dirPin 16
#define stepPin 17
#define motorInterfaceType 1
// Create a new instance of the AccelStepper class:
AccelStepper Feeder::stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void Feeder::rotate()
{
	Feeder::stepper.move(100);
}

void Feeder::initialize()
{
	Feeder::stepper.setMaxSpeed(100);
	Feeder::stepper.setAcceleration(100);
}

void Feeder::loop()
{
	Feeder::stepper.run();
}
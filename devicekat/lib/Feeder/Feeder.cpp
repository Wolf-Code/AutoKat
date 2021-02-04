#include "Feeder.h"
#include <AccelStepper.h>

#define MotorInterfaceType 8
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper library with 28BYJ-48 stepper motor:
AccelStepper Feeder::stepper(MotorInterfaceType, 16, 17, 18, 19);

void Feeder::rotate()
{
	Feeder::stepper.move(2038);
}

void Feeder::initialize()
{
	Feeder::stepper.setMaxSpeed(1000);
	Feeder::stepper.setAcceleration(400);
}

void Feeder::loop()
{
	Feeder::stepper.run();
}
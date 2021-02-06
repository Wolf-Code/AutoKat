#include "Bowl.h"

Servo Bowl::servo;
bool Bowl::opened;

void Bowl::ensureAttached() 
{
    if(!Bowl::servo.attached())
    {
        Bowl::servo.attach(18);
    }
}

void Bowl::open()
{
    Bowl::ensureAttached();
    Bowl::servo.write(10);
    Bowl::opened = true;
    delay(200);
    Bowl::servo.detach();
}

void Bowl::close()
{
    Bowl::ensureAttached();
    Bowl::servo.write(165);
    Bowl::opened = false;
    delay(200);
    Bowl::servo.detach();
}

bool Bowl::isOpen()
{
    return Bowl::opened;
}
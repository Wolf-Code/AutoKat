#ifndef __BOWL_H__
#define __BOWL_H__

#include <ESP32Servo.h>

class Bowl {
    public:
        static void open();
        static void close();
        static bool isOpen();

    private:
        static Servo servo;
        static bool opened;
        static void ensureAttached();
};

#endif
#pragma once
#include <Servo.h>
#include "octosnake.h"
#include "../mind/mind.h"

class Joint {
    public:
        Joint() = delete;
        Joint(int pin, int trim, bool reverse);
        void pulse();
        Oscillator oscillator;
        void setPosition(float target);
        float getPosition();
        void oscillate(int period, int amplitude, int phase, int offset);
    private:
        bool reverse;
        int pin;
        int trim; // not sure we need it... but the trim may be set directly in Oscilator on init.
                  // we may need some lifecycle here.
        Servo servo;
        float _position;
        int angToUsec(float value);
        float _basePosition = 90;
        // float _basePosition = 75;
        bool oscillating = false;
        unsigned long osc_until;
};
#pragma once
#include <Servo.h>
#include "soul/octosnake.h"
#include "soul/threelaws.h"
#include "mind/mind.h"

class Joint {
    public:
        Joint() = delete;
        Joint(int pin, int trim, bool reverse);
        void stop_work();
        void pulse();
        Oscillator oscillator;
        void setPosition(float target);
        float getPosition();
        void oscillate(int period, int amplitude, int phase, int offset);
        void setTrim(int trim);
        void setTilt(int trim);
    private:
        bool reverse;
        int pin;
        int trim;
        int tilt = 0;
        Servo servo;
        float _position;
        int angToUsec(float value);
        float _basePosition = 90;
        bool oscillating = false;
};
#include "joint.h"

int Joint::angToUsec(float value){
    return value/180 * (DEFAULT_MAX_PULSE_WIDTH-DEFAULT_MIN_PULSE_WIDTH) + DEFAULT_MIN_PULSE_WIDTH;
}

Joint::Joint(int pin, int calibrationTrim, bool reverse) {
    this->pin = pin;
    this->_calibrationTrim = calibrationTrim;
    this->trim = 0;
    this->reverse = reverse;
    this->servo.attach(this->pin);
    this->oscillator.setTrim(this->_calibrationTrim);
}

void Joint::setPosition(float target){
    const int limit = 90;
    if (!ThreeLawsOfRobotics::conforms()) {
        Serial.println("SEVERE! Violation of the Laws of Robotics detected!");
        return;
    }

    int totalTrim = this->_calibrationTrim + this->trim + this->tilt;

    if ((target + totalTrim) > limit) {
        target = limit - totalTrim;
    } else if ((target + totalTrim) < -limit) {
        target = -limit - totalTrim;
    }
 
    if (!this->reverse) {
        this->servo.writeMicroseconds(this->angToUsec(this->_basePosition + target + totalTrim));
    }
    else {
        this->servo.writeMicroseconds(this->angToUsec(180 - (this->_basePosition + target + totalTrim)));
    }

    this->_position = target;
}

float Joint::getPosition(){
    return this->_position;
}

void Joint::oscillate(int period, int amplitude, int phase, int offset) {
    if (!this->oscillating) {
        this->oscillator.setPeriod(period / Mind::getSpeedModifier());
        this->oscillator.setAmplitude(amplitude);
        this->oscillator.setPhase(phase);
        this->oscillator.setOffset(offset);

        this->oscillator.reset();
        this->oscillating = true;
    }
}

void Joint::setTrim(int trim) {
    this->trim = trim;
    this->oscillator.setTrim(this->_calibrationTrim + this->trim + this->tilt);
    if (!this->oscillating) {
        this->setPosition(this->_position);
    }
}

void Joint::setTilt(int tilt) {
    this->tilt = tilt;
    this->oscillator.setTrim(this->_calibrationTrim + this->trim + this->tilt);
    if (!this->oscillating) {
        this->setPosition(this->_position);
    }
}

void Joint::stop_work() {
    // invalidate
    this->oscillating = false;
    this->oscillator.reset();
}

void Joint::pulse() {
    if (this->oscillating) {
        this->setPosition(this->oscillator.refresh());
    }
}
#include "joint.h"

int Joint::angToUsec(float value){
    return value/180 * (DEFAULT_MAX_PULSE_WIDTH-DEFAULT_MIN_PULSE_WIDTH) + DEFAULT_MIN_PULSE_WIDTH;
}

Joint::Joint(int pin, int trim, bool reverse) {
    this->pin = pin;
    this->trim = trim;
    this->reverse = reverse;
    this->servo.attach(this->pin);
    this->oscillator.setTrim(0);
}

void Joint::setPosition(float target){
    const int limit = 90;
    if (!ThreeLawsOfRobotics::conforms()) {
        Serial.println("SEVERE! Violation of the Laws of Robotics detected!");
        return;
    }
    if ((target + this->trim + this->tilt) > limit) {
        target = limit - this->trim - this->tilt;
    } else if ((target + this->trim + this->tilt) < -limit) {
        target = -limit - this->trim - this->tilt;
    }
 
    if (!this->reverse) {
        this->servo.writeMicroseconds(this->angToUsec(this->_basePosition + target + this->trim + this->tilt));
    }
    else {
        this->servo.writeMicroseconds(this->angToUsec(180 - (this->_basePosition + target + this->trim + this->tilt)));
    }

    this->_position = target;
}

float Joint::getPosition(){
    return this->_position;
}

void Joint::oscillate(int period, int amplitude, int phase, int offset) {
    this->_basePeriod = period;
    this->_lastSpeed = Mind::getSpeedModifier();
    if (this->_lastSpeed <= 0) {
        this->_lastSpeed = 1.0f;
    }
    this->oscillator.setPeriod(this->_basePeriod / this->_lastSpeed);
    this->oscillator.setAmplitude(amplitude);
    this->oscillator.setPhase(phase);
    this->oscillator.setOffset(offset);

    if (!this->oscillating) {
        this->oscillator.reset();
        this->oscillating = true;
    }
}

void Joint::setTrim(int trim) {
    this->trim = trim;
    if (!this->oscillating) {
        this->setPosition(this->_position);
    }
}

void Joint::setTilt(int tilt) {
    this->tilt = tilt;
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
        float currentSpeed = Mind::getSpeedModifier();
        if (currentSpeed != this->_lastSpeed && currentSpeed > 0) {
            this->_lastSpeed = currentSpeed;
            this->oscillator.setPeriod(this->_basePeriod / currentSpeed);
        }
        this->setPosition(this->oscillator.refresh());
    }
}
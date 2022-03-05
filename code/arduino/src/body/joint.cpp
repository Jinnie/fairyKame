#include "joint.h"

int Joint::angToUsec(float value){
    return value/180 * (DEFAULT_MAX_PULSE_WIDTH-DEFAULT_MIN_PULSE_WIDTH) + DEFAULT_MIN_PULSE_WIDTH;
}

Joint::Joint(int pin, int trim, bool reverse) {
    this->pin = pin;
    this->trim = trim;
    this->reverse = reverse;
    this->servo.attach(this->pin);
    this->oscillator.setTrim(this->trim);
}

void Joint::setPosition(float target){
    const int limit = 90;
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
    this->oscillator.setTrim(trim);
    if (!this->oscillating) {
        this->setPosition(this->_position);
    }
}

void Joint::setTilt(int tilt) {
    this->tilt = tilt;
    this->oscillator.setTrim(this->trim + this->tilt);
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
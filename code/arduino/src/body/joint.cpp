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
    const int limit = 70;
    if (target > limit || target < -limit) {
        Serial.print("wrong position ");
        Serial.println(target);
        target = target > limit ? limit : -limit;
    }
    if (!this->reverse)
        this->servo.writeMicroseconds(this->angToUsec(this->_basePosition + target + this->trim)); // todo: make trim reverse sensitive
    else
        this->servo.writeMicroseconds(this->angToUsec(180 - (this->_basePosition + target + this->trim)));
    this->_position = target;
}

float Joint::getPosition(){
    return this->_position;
}

void Joint::oscillate(int period, int amplitude, int phase, int offset) {
    if (!this->oscillating) {
        this->oscillator.setPeriod(period);
        this->oscillator.setAmplitude(amplitude);
        this->oscillator.setPhase(phase);
        this->oscillator.setOffset(offset);

        this->oscillator.reset();
        this->osc_until = this->oscillator.getTime() + period; // period*steps !?!?
        this->oscillating = true;
    }
}

void Joint::pulse() {
    if (Mind::in_rest()) {
        // invalidate
        this->oscillator.reset();
        this->osc_until = millis() - 1;
    }
    if (this->oscillating) {
        if (millis() < this->osc_until) {
            Serial.println(".");
            this->setPosition(this->oscillator.refresh());
            // yield(); //todo: check if needed
        } else {
            this->oscillating = false;
            Serial.println("------");
        }
    }
}
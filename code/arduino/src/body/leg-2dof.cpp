#include "leg-2dof.h"

// board_pins[0] = D1; // front left inner
// board_pins[1] = D4, // front right inner
// board_pins[2] = D8; // front left outer
// board_pins[3] = D6; // front right outer
// board_pins[4] = D7; // back left inner
// board_pins[5] = D5; // back right inner
// board_pins[6] = D2; // back left outer
// board_pins[7] = D3; // back right outer

Leg2DOF::Leg2DOF(bool front, bool left) {
    this->front = front;
    this->left = left;
    const bool clockwise = false;
    const bool anticlock = true;
    // TODO: Recalibrate your robot to trim = 0
    const int TRIM_HEIGHT = -20;
    const int TRIM_SPREAD = 10;
    if (this->front) {
        if (this->left) {
            this->hip = new Joint(D1, TRIM_SPREAD, clockwise);
            this->knee = new Joint(D8, TRIM_HEIGHT, clockwise);
        } else {
            this->hip = new Joint(D4, TRIM_SPREAD, anticlock);
            this->knee = new Joint(D6, TRIM_HEIGHT, anticlock);
        }
    } else {
        if (this->left) {
            this->hip = new Joint(D7, -TRIM_SPREAD, clockwise);
            this->knee = new Joint(D2, TRIM_HEIGHT, anticlock);
        } else {
            this->hip = new Joint(D5, -TRIM_SPREAD, anticlock);
            this->knee = new Joint(D3, TRIM_HEIGHT, clockwise);
        }
    }
}

void Leg2DOF::walk(int period, int amplitude, int phase, const int offsets[2], bool backward) {
    // Cross sync for the case when we have different directions for different legs.
    phase += backward ? 90 : 0;

    this->hip->oscillate(period, amplitude, phase, offsets[0]);
    int kneePhase = phase + (backward ? -90 : 90);
    // int kneePhase =  (phase + 90) * (backward ? -1 : 1);
    this->knee->oscillate(period, amplitude, kneePhase, offsets[1]);

    Serial.print(phase); Serial.print(' '); Serial.print(kneePhase); Serial.print(' ');
    Serial.println(phase - kneePhase);
}

void Leg2DOF::walk(Gait gait) {
    int offsets[2] = {gait.position.height, gait.position.spread};
    walk(gait.period, gait.amplitude, gait.phase, offsets, gait.direction);
}

void Leg2DOF::relax() {
    this->hip->setPosition(0);
    this->knee->setPosition(0);
}

void Leg2DOF::pulse() {
    this->hip->pulse();
    this->knee->pulse();
}

Leg2DOF::~Leg2DOF() {
    delete this->hip;
    delete this->knee;
}
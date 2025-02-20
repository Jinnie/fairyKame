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
    // You can hardcode your trim here
    // Todo: make possible to trim each leg separately.
    const int TRIM_HEIGHT = 0;
    const int TRIM_SPREAD = 0;

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

// TODO: test adding non-circular amplitudes
void Leg2DOF::walk(int period, Pair amplitude, int phase, const Pair offsets, bool backward) {
    // Cross sync for the case when we have different directions for different legs.
    phase += backward ? 90 : 0;

    this->hip->oscillate(period, amplitude.spread, phase, offsets.spread);
    int kneePhase = phase + (backward ? -90 : 90);
    this->knee->oscillate(period, amplitude.height, kneePhase, offsets.height);
}

void Leg2DOF::walk(Gait gait) {
    walk(gait.period, gait.amplitude, gait.phase, gait.position, gait.direction);
}

void Leg2DOF::flex(int period, int amplitude, int phase, const Pair offsets) {
    this->hip->setPosition(offsets.spread);
    this->knee->oscillate(period, amplitude, phase, offsets.height);
}

void Leg2DOF::pose(int hip, int knee) {
    this->hip->setPosition(hip);
    this->knee->setPosition(knee);
}

void Leg2DOF::relax() {
    pose(0, 0);
}

void Leg2DOF::stop_work() {
    this->hip->stop_work();
    this->knee->stop_work();
}

void Leg2DOF::pulse() {
    this->hip->pulse();
    this->knee->pulse();
    if (Mind::getHeightOverride() != this->heightOverride) {
        this->heightOverride = Mind::getHeightOverride();
        this->knee->setTrim(this->heightOverride);
    }
    if (Mind::getTiltCorrection() != this->tiltCorrection) {
        this->tiltCorrection = Mind::getTiltCorrection();
        this->knee->setTilt(this->left ? this->tiltCorrection : -this->tiltCorrection);
    }
}

Leg2DOF::~Leg2DOF() {
    delete this->hip;
    delete this->knee;
}
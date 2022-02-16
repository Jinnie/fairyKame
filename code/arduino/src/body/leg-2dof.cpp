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
    if (this->front) {
        if (this->left) {
            this->hip = new Joint(D1, 0, clockwise);
            this->knee = new Joint(D8, 0, clockwise);
        } else {
            this->hip = new Joint(D4, 0, anticlock);
            this->knee = new Joint(D6, 0, anticlock);
        }
    } else {
        if (this->left) {
            this->hip = new Joint(D7, 0, clockwise);
            this->knee = new Joint(D2, 0, anticlock);
        } else {
            this->hip = new Joint(D5, 0, anticlock);
            this->knee = new Joint(D3, 0, clockwise);
        }
    }
}

void Leg2DOF::pulse() {
    this->hip->pulse();
    this->knee->pulse();
}

Leg2DOF::~Leg2DOF() {
    delete this->hip;
    delete this->knee;
}
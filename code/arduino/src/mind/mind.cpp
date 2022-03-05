#include "mind.h"

static int _height = 0;
static int _tilt = 0;
static float _speed = 1;

int Mind::getHeightOverride() {
    return _height;
}

void Mind::setHeightOverride(int height) {
    _height = height;
}

int Mind::getTiltCorrection() {
    return _tilt;
}

void Mind::setTiltCorrection(int tilt) {
    _tilt = tilt;
}

float Mind::getSpeedModifier() {
    return _speed;
}

void Mind::setSpeedModifier(float speed) {
    _speed = speed;
}
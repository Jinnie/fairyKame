#include "mind.h"

static bool _work;

static int _height = 0;

static int _tilt = 0;

bool Mind::in_rest() {
    return !_work;
}

void Mind::stop_work() {
    _work = false;
}

void Mind::start_work() {
    _work = true;
}

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
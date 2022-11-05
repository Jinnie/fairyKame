#include "mind.h"

static int _height = 0;
static int _tilt = 0;
static int _delay = 20;
static float _speed = 1;
static String _activeCommand = "stop";

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

int Mind::getDelay() {
    return _delay;
}

void Mind::setDelay(int delay) {
    _delay = delay;
}

float Mind::getSpeedModifier() {
    return _speed;
}

void Mind::setSpeedModifier(float speed) {
    _speed = speed;
}

String Mind::getActiveCommand() {
    return _activeCommand;
}

void Mind::setActiveCommand(String activeCommand) {
    _activeCommand = activeCommand;
}
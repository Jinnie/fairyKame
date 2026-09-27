#include "mind.h"

static int _height = 0;
static int _tilt = 0;
static int _delay = 12;
static float _speed = 1;
static String _activeCommand = "idle";
static bool _idleMode = true;
static unsigned long _movementEndTime = 0;
static MoveSpec _dynamicSpec;
static bool _hasDynamicSpec = false;

static bool _isMovingCommand(const String& cmd) {
    return (cmd.length() > 0 && cmd != "stop" && cmd != "relax" && cmd != "idle");
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
    if (activeCommand != "__dynamic__") {
        _hasDynamicSpec = false;
    }
    // If transitioning from an active movement to stop/idle, stamp recovery timer
    if (_isMovingCommand(_activeCommand) && (activeCommand == "stop" || activeCommand == "idle")) {
        _movementEndTime = millis();
    }
    if (activeCommand == "stop" && _idleMode) {
        activeCommand = "idle";
    }
    if (_activeCommand != activeCommand) {
        Serial.print('#');
        Serial.println(activeCommand);
        _activeCommand = activeCommand;
    }
}

void Mind::getPantingFactors(float& speedFactor, float& ampFactor) {
    if (_movementEndTime == 0) {
        speedFactor = 1.0f;
        ampFactor   = 1.0f;
        return;
    }
    unsigned long elapsed = millis() - _movementEndTime;
    const unsigned long RECOVERY_TIME_MS = 20000;
    if (elapsed < RECOVERY_TIME_MS) {
        float progress = 1.0f - ((float)elapsed / (float)RECOVERY_TIME_MS);
        speedFactor = 1.0f + 0.40f * progress;
        ampFactor   = 1.0f + 0.20f * progress;
    } else {
        speedFactor = 1.0f;
        ampFactor   = 1.0f;
    }
}

void Mind::triggerPanting() {
    _movementEndTime = millis();
}

bool Mind::getIdleMode() {
    return _idleMode;
}

void Mind::setIdleMode(bool enabled) {
    _idleMode = enabled;
    if (_idleMode) {
        triggerPanting();
        if (_activeCommand == "stop" || _activeCommand == "relax" || _activeCommand == "") {
            setActiveCommand("idle");
        }
    } else {
        if (_activeCommand == "idle") {
            setActiveCommand("stop");
        }
    }
}

static bool _dynamicSpecDirty = false;

void Mind::setDynamicSpec(const MoveSpec& spec) {
    _dynamicSpec = spec;
    _hasDynamicSpec = true;
    _dynamicSpecDirty = true;
    setActiveCommand("__dynamic__");
}

const MoveSpec& Mind::getDynamicSpec() {
    return _dynamicSpec;
}

bool Mind::isDynamicSpec() {
    return _hasDynamicSpec && _activeCommand == "__dynamic__";
}

bool Mind::isDynamicSpecDirty() {
    return _dynamicSpecDirty;
}

void Mind::clearDynamicSpecDirty() {
    _dynamicSpecDirty = false;
}
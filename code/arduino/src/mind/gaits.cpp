#include "gaits.h"

Position::Position() {}

Position::Position(int height, int spread) {
    this->height = height;
    this->spread = spread;
}

Gait Gaits::steadyGait(int phase, bool direction) {
    Gait g;
    g.period = 700;
    g.amplitude = 20;
    g.direction = direction;
    g.phase = phase;
    return g;
}

Gait Gaits::steadyShortGait(int phase, bool direction) {
    Gait g;
    g.period = 700;
    g.amplitude = 10;
    g.direction = direction;
    g.phase = phase;
    return g;
}

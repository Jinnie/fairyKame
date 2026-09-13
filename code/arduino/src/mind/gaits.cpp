#include "gaits.h"

Pair::Pair() {}

Pair::Pair(int spread, int height) {
    this->height = height;
    this->spread = spread;
}

Gait Gaits::steadyGait(int phase, bool direction) {
    Gait g;
    g.period = 700;
    g.amplitude = {20, 20};
    g.direction = direction;
    g.phase = phase;
    return g;
}

Gait Gaits::steadyShortGait(int phase, bool direction) {
    Gait g;
    g.period = 700;
    g.amplitude = {5, 20};
    g.direction = direction;
    g.phase = phase;
    return g;
}

Gait Gaits::shortRapidGait(int phase, bool direction) {
    Gait g;
    g.period = 350;
    g.amplitude = {10, 15};
    g.direction = direction;
    g.phase = phase;
    return g;
}

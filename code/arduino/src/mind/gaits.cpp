#include "gaits.h"

Pair::Pair() {}

Pair::Pair(int spread, int height) {
    this->height = height;
    this->spread = spread;
}

Gait Gaits::steadyGait(int phase, bool direction) {
    Gait g;
    g.period = 700;
    g.amplitude = Pair(20, 20);
    g.direction = direction;
    g.phase = phase;
    return g;
}

Gait Gaits::steadyShortGait(int phase, bool direction) {
    Gait g;
    g.period = 700;
    g.amplitude = Pair(5, 20);
    g.direction = direction;
    g.phase = phase;
    return g;
}

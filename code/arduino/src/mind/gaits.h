#pragma once

/**
 * @brief Predefined gaits that require minimal configurations.
 * You can copy/paste and adjust them for more complex or customized gaits.
 */

class Pair {
    public:
        int height = 0;
        int spread = 0;
        Pair();
        Pair(int spread, int height);
};

class Gait {
    public:
        static const bool FORWARD = false;
        static const bool BACKWARD = true;
        int period = 700;
        Pair amplitude = {20, 20};
        int phase = 0;
        bool direction = FORWARD;
        Pair position = {0, 0};

        Gait() = default;
        Gait(int period, Pair amplitude, int phase, Pair position, bool direction = FORWARD)
            : period(period), amplitude(amplitude), phase(phase), direction(direction), position(position) {}

        Gait withPhase(int p) const { Gait g = *this; g.phase = p; return g; }
        Gait withPeriod(int t) const { Gait g = *this; g.period = t; return g; }
        Gait withAmplitude(Pair amp) const { Gait g = *this; g.amplitude = amp; return g; }
        Gait withPosition(Pair pos) const { Gait g = *this; g.position = pos; return g; }
        Gait withSpread(int s) const { Gait g = *this; g.position.spread = s; return g; }
        Gait withHeight(int h) const { Gait g = *this; g.position.height = h; return g; }
        Gait withDirection(bool dir) const { Gait g = *this; g.direction = dir; return g; }
};

class Flex {
    public:
        int period = 500;
        int amplitude = 30;
        int phase = 0;
        Pair position = {0, 0};

        Flex() = default;
        Flex(int period, int amplitude, int phase, Pair position = {0, 0})
            : period(period), amplitude(amplitude), phase(phase), position(position) {}

        Flex withPhase(int p) const { Flex f = *this; f.phase = p; return f; }
        Flex withPeriod(int t) const { Flex f = *this; f.period = t; return f; }
        Flex withAmplitude(int a) const { Flex f = *this; f.amplitude = a; return f; }
        Flex withPosition(Pair pos) const { Flex f = *this; f.position = pos; return f; }
        Flex withSpread(int s) const { Flex f = *this; f.position.spread = s; return f; }
        Flex withHeight(int h) const { Flex f = *this; f.position.height = h; return f; }
};

class Gaits {
    public:
        static Gait steadyGait(int phase, bool direction);
        static Gait steadyShortGait(int phase, bool direction);
        static Gait shortRapidGait(int phase, bool direction);
};
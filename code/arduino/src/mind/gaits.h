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
        int period;
        Pair amplitude;
        int phase = 0;
        bool direction = FORWARD;
        Pair position;
};

class Gaits {
    public:
        static Gait steadyGait(int phase, bool direction);
        static Gait steadyShortGait(int phase, bool direction);
        static Gait shortRapidGait(int phase, bool direction); //DZAK! todo
};
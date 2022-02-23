#pragma once

/**
 * @brief Predefined gaits that require minimal configurations.
 * You can copy/paste and adjust them for more complex or customized gaits.
 */

class Position {
    public:
        int height = 0;
        int spread = 0;
        Position();
        Position(int height, int spread);
};

class Gait {
    public:
        static const bool FORWARD = false;
        static const bool BACKWARD = true;
        int period;
        int amplitude;
        int phase = 0;
        bool direction = FORWARD;
        Position position;
};

class Gaits {
    public:
        static Gait steadyGait(int phase, bool direction);
        static Gait steadyShortGait(int phase, bool direction);
        static Gait shortRapidGait(int phase, bool direction); //DZAK! todo
};
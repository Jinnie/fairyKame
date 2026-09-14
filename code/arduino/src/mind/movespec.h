#pragma once

#include <Arduino.h>
#include "mind/gaits.h"

/**
 * @brief Execution mode for an individual 2-DOF leg.
 */
enum class LegMode : uint8_t {
    POSE, // Static posture target {spread, height}
    FLEX, // 1-DOF knee oscillation with static hip spread
    WALK  // 2-DOF coordinated sinusoidal walking gait
};

/**
 * @brief Complete kinematic specification for an individual 2-DOF leg.
 */
struct LegSpec {
    LegMode mode = LegMode::POSE;
    int16_t period = 0;
    int8_t  ampSpread = 0;
    int8_t  ampHeight = 0;
    int16_t phase = 0;
    int8_t  offsetSpread = 0;
    int8_t  offsetHeight = 0;
    bool    backward = false;

    static LegSpec Pose(int8_t spread, int8_t height) {
        LegSpec s;
        s.mode = LegMode::POSE;
        s.offsetSpread = spread;
        s.offsetHeight = height;
        return s;
    }

    static LegSpec Flex(int16_t period, int8_t ampHeight, int16_t phase, int8_t spread, int8_t height) {
        LegSpec s;
        s.mode = LegMode::FLEX;
        s.period = period;
        s.ampHeight = ampHeight;
        s.phase = phase;
        s.offsetSpread = spread;
        s.offsetHeight = height;
        return s;
    }

    static LegSpec Walk(int16_t period, int8_t ampSpread, int8_t ampHeight, int16_t phase, int8_t spread, int8_t height, bool backward = false) {
        LegSpec s;
        s.mode = LegMode::WALK;
        s.period = period;
        s.ampSpread = ampSpread;
        s.ampHeight = ampHeight;
        s.phase = phase;
        s.offsetSpread = spread;
        s.offsetHeight = height;
        s.backward = backward;
        return s;
    }

    static LegSpec FromGait(const Gait& g) {
        return Walk(g.period, g.amplitude.spread, g.amplitude.height, g.phase, g.position.spread, g.position.height, g.direction);
    }
};

/**
 * @brief Complete 4-leg posture or motion spec for FairyKame.
 */
struct MoveSpec {
    const char* name;
    LegSpec fl; // Front Left
    LegSpec fr; // Front Right
    LegSpec bl; // Back Left
    LegSpec br; // Back Right
};

/**
 * @brief Registry of all predefined, data-driven move specs.
 */
class MoveRegistry {
public:
    static const MoveSpec* find(const String& name);
    static const MoveSpec* getAll(size_t& count);
};

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
 * @brief Expressive kinematic specification for an individual 2-DOF leg.
 * First-class support for Gait, Pair (pose), and Flex.
 */
class LegSpec {
public:
    LegMode mode = LegMode::POSE;
    Gait    gait;
    Pair    pose;
    Flex    flex;

    LegSpec() : mode(LegMode::POSE), pose(0, 0) {}

    // First-class constructors from domain primitives
    LegSpec(const Gait& g) : mode(LegMode::WALK), gait(g) {}
    LegSpec(const Pair& p) : mode(LegMode::POSE), pose(p) {}
    LegSpec(int spread, int height) : mode(LegMode::POSE), pose(spread, height) {}
    LegSpec(const Flex& f) : mode(LegMode::FLEX), flex(f) {}
};

/**
 * @brief Complete 4-leg posture or motion spec for FairyKame.
 */
struct MoveSpec {
    const char* name = nullptr;
    LegSpec fl; // Front Left
    LegSpec fr; // Front Right
    LegSpec bl; // Back Left
    LegSpec br; // Back Right

    MoveSpec() = default;
    MoveSpec(const char* name, LegSpec fl, LegSpec fr, LegSpec bl, LegSpec br)
        : name(name), fl(fl), fr(fr), bl(bl), br(br) {}

    // Convenience constructor for symmetric 4-leg pose
    MoveSpec(const char* name, const Pair& allLegs)
        : name(name), fl(allLegs), fr(allLegs), bl(allLegs), br(allLegs) {}
};

/**
 * @brief Registry of all predefined, data-driven move specs.
 */
class MoveRegistry {
public:
    static const MoveSpec* find(const String& name);
    static const MoveSpec* getAll(size_t& count);
};

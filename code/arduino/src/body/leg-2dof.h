#pragma once

#include "joint.h"
#include "mind/gaits.h"

class Leg2DOF {
  public:
    Leg2DOF() = delete;
    Leg2DOF(bool left, bool front);
    ~Leg2DOF();
    void pulse();
    Joint *hip{};
    Joint *knee{};

    // Save the initilizer list version
    // void walk(int period, int amplitude, int phase, const std::initializer_list<int>& offsets, bool backward);

    // direct parameter set
    void walk(int period, int amplitude, int phase, const int offsets[2], bool backward);
    // alternative gait based
    void walk(Gait gait);
    void flex(int period, int amplitude, int phase, const int offsets[2]);
    void pose(int hip, int knee);
    void relax();
  private:
    // these, honestly, should be enums, but naming the 2 enums readably is pain. left/right can be Side. But what about front/back
    bool left;  // lefthand
    bool front;  // front/rear
};

#pragma once

#include "joint.h"

class Leg2DOF {
  public:
    Leg2DOF() = delete;
    Leg2DOF(bool left, bool front);
    ~Leg2DOF();
    void pulse();
    Joint *hip{};
    Joint *knee{};

    void walk(int period, int amplitude, int phase, const std::initializer_list<int>& offsets, bool backward);
  private:
    // these, honestly, should be enums, but naming the 2 enums readably is pain. left/right can be Side. But what about front/back
    bool left;  // lefthand
    bool front;  // front/rear
};

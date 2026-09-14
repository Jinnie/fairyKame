#pragma once
#include <Arduino.h>
#include "mind/movespec.h"

class Mind {
    public:
        static int getHeightOverride();
        static void setHeightOverride(int height);
        static int getTiltCorrection();
        static void setTiltCorrection(int tilt);
        static int getDelay();
        static void setDelay(int delay);
        static float getSpeedModifier();
        static void setSpeedModifier(float speed);
        static String getActiveCommand();
        static void setActiveCommand(String activeCommand);

        static void setDynamicSpec(const MoveSpec& spec);
        static const MoveSpec& getDynamicSpec();
        static bool isDynamicSpec();
};
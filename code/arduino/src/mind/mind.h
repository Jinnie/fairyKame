#pragma once

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
};
#pragma once

class Mind {
    public:
        static int getHeightOverride();
        static void setHeightOverride(int height);
        static int getTiltCorrection();
        static void setTiltCorrection(int tilt);
        static float getSpeedModifier();
        static void setSpeedModifier(float speed);
};
#pragma once

class Mind {
    public:
        static bool in_rest();
        static void start_work();
        static void stop_work();
        static int getHeightOverride();
        static void setHeightOverride(int height);
        static int getTiltCorrection();
        static void setTiltCorrection(int tilt);
};
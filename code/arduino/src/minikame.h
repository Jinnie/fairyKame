#ifndef minikame_h
#define minikame_h

#include <Servo.h>
#include "soul/octosnake.h"
#include "body/leg-2dof.h"
#include "mind/gaits.h"

class MiniKame {

    public:
        MiniKame();
        ~MiniKame();
        void init();
        void stop_work();
        void pulse();

        // gaits
        void just_walk();
        void just_relax();
        void just_dance();
        void just_back();
        void just_left();
        void just_right();
        void just_upLeft();
        void just_upRight();
        void just_backLeft();
        void just_backRight();
        void just_jiggle();
        void just_moonwalk();
        void just_stretch();
        void just_confused();
        void just_pushUps();
        void just_say_hi();
        void just_pack();
        void just_strafe_left();
        void just_strafe_right();
        void magic();

    private:
        Leg2DOF *frontLeftLeg;
        Leg2DOF *frontRightLeg;
        Leg2DOF *backLeftLeg;
        Leg2DOF *backRightLeg;
};

#endif

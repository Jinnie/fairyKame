#ifndef minikame_h
#define minikame_h

#include <Servo.h>
#include "octosnake.h"
#include "body/leg-2dof.h"
#include "mind/gaits.h"

class MiniKame {

    public:
        ~MiniKame();
        void init();
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
        void magic();

    private:
        Leg2DOF *frontLeftLeg = new Leg2DOF(true, true);
        Leg2DOF *frontRightLeg = new Leg2DOF(true, false);
        Leg2DOF *backLeftLeg = new Leg2DOF(false, true);
        Leg2DOF *backRightLeg = new Leg2DOF(false, false);
};

#endif

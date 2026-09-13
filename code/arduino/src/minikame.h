#ifndef minikame_h
#define minikame_h

#include "body/leg-2dof.h"
#include "mind/gaits.h"

class MiniKame {

    public:
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

        // expressive moves & tricks
        void just_turn_in_place(bool left);
        void just_crawl();
        void just_tiptoe();
        void just_recover();
        void just_sit();
        void just_play_dead();
        void just_shiver();
        void just_scratch_ear();
        void just_pounce_prep();
        void just_wave_goodbye();
        void just_tap_foot();

    private:
        Leg2DOF *frontLeftLeg = new Leg2DOF(true, true);
        Leg2DOF *frontRightLeg = new Leg2DOF(true, false);
        Leg2DOF *backLeftLeg = new Leg2DOF(false, true);
        Leg2DOF *backRightLeg = new Leg2DOF(false, false);
};

#endif

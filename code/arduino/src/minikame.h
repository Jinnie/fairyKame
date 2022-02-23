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

        // void run(float steps, float period);
        // void walk(float steps, float period);
        //void backward(float steps, float period);
        // void turnL(float steps, float period);
        // void turnR(float steps, float period);
        // void moonwalkL(float steps, float period);
        // void dance(float steps, float period);
        // void upDown(float steps, float period);
        // void pushUp(float steps, float period);
        // void hello();
        // void jump();
        // void home();
        // void zero();
        // void frontBack(float steps, float period);

        // void setServo(int id, float target);
        // void reverseServo(int id);
        // float getServo(int id);
        // void moveServos(int time, float target[8]);

        // new gaits
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
        void magic();

    private:
        Oscillator oscillator[8];
        Servo servo[8];
        int board_pins[8];
        int trim[8];
        bool reverse[8];
        unsigned long _init_time;
        unsigned long _final_time;
        unsigned long _partial_time;
        float _increment[8];
        float _servo_position[8];

        //int angToUsec(float value);
        void execute(float steps, float period[8], int amplitude[8], int offset[8], int phase[8]);

        Leg2DOF *frontLeftLeg = new Leg2DOF(true, true);
        Leg2DOF *frontRightLeg = new Leg2DOF(true, false);
        Leg2DOF *backLeftLeg = new Leg2DOF(false, true);
        Leg2DOF *backRightLeg = new Leg2DOF(false, false);
};

#endif

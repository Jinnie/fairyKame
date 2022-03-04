#include "minikame.h"

void MiniKame::init()
{
    just_relax();
}

void MiniKame::stop_work()
{
    this->frontLeftLeg->stop_work();
    this->frontRightLeg->stop_work();
    this->backLeftLeg->stop_work();
    this->backRightLeg->stop_work();
}

void MiniKame::pulse()
{
    this->frontLeftLeg->pulse();
    this->frontRightLeg->pulse();
    this->backLeftLeg->pulse();
    this->backRightLeg->pulse();
}

void MiniKame::just_relax()
{

    this->frontLeftLeg->relax();
    this->frontRightLeg->relax();
    this->backLeftLeg->relax();
    this->backRightLeg->relax();
}

void MiniKame::just_walk()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
    this->backRightLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
}

void MiniKame::just_back()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(180, Gait::BACKWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(180, Gait::BACKWARD));
    this->backRightLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
}

void MiniKame::just_dance()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
    this->backRightLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
}

void MiniKame::just_left()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(180, Gait::BACKWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
    this->backRightLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
}

void MiniKame::just_right()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(180, Gait::BACKWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
    this->backRightLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
}

void MiniKame::just_upLeft()
{
    this->frontLeftLeg->walk(Gaits::steadyShortGait(0, Gait::FORWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
    this->backLeftLeg->walk(Gaits::steadyShortGait(180, Gait::FORWARD));
    this->backRightLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
}
void MiniKame::just_upRight()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
    this->frontRightLeg->walk(Gaits::steadyShortGait(180, Gait::FORWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(180, Gait::FORWARD));
    this->backRightLeg->walk(Gaits::steadyShortGait(0, Gait::FORWARD));
}

void MiniKame::just_backLeft()
{
    this->frontLeftLeg->walk(Gaits::steadyShortGait(0, Gait::BACKWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(180, Gait::BACKWARD));
    this->backLeftLeg->walk(Gaits::steadyShortGait(180, Gait::BACKWARD));
    this->backRightLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
}
void MiniKame::just_backRight()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(0, Gait::BACKWARD));
    this->frontRightLeg->walk(Gaits::steadyShortGait(180, Gait::BACKWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(180, Gait::BACKWARD));
    this->backRightLeg->walk(Gaits::steadyShortGait(0, Gait::BACKWARD));
}

void MiniKame::just_jiggle()
{
    this->frontLeftLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
    this->frontRightLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
    this->backLeftLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
    this->backRightLeg->walk(Gaits::steadyGait(0, Gait::FORWARD));
}

void MiniKame::just_confused()
{
    Pair shrug = {0, 60};
    this->frontLeftLeg->flex(200, 15, 0, shrug);
    this->frontRightLeg->flex(200, 15, 0, shrug);
    this->backLeftLeg->flex(200, 15, 0, shrug);
    this->backRightLeg->flex(200, 15, 0, shrug);
};

void MiniKame::just_pushUps()
{
    this->frontLeftLeg->flex(1400, 65, 0, {-10, -30});
    this->frontRightLeg->flex(1400, 65, 0, {-10, -30});
    this->backLeftLeg->pose(-90, -30); // 90 is a bit too much, check after recalibration.
    this->backRightLeg->pose(-90, -30);
}

void MiniKame::just_moonwalk() {
    Pair front_position = {-20, 30};
    Pair back_position = {20, 30};
    this->frontLeftLeg->flex(2000, 45, 0, front_position);
    this->frontRightLeg->flex(2000, 45, 120, front_position);
    this->backLeftLeg->flex(2000, 45, 0, back_position);
    this->backRightLeg->flex(2000, 45, 120, back_position);
}

void MiniKame::just_stretch() {
    Pair position = {0, -20};
    this->frontLeftLeg->flex(2000, 45, 0, position);
    this->frontRightLeg->flex(2000, 45, 120, position);
    this->backLeftLeg->flex(2000, 45, 180, position);
    this->backRightLeg->flex(2000, 45, 290, position);
}

void MiniKame::just_say_hi() {
    this->frontLeftLeg->pose(50, -40);
    this->backLeftLeg->pose(-50, 50);
    this->backRightLeg->pose(20, -25);
    this->frontRightLeg->flex(300, 30, 0, {60, 60});
}

void MiniKame::magic() {
    // say hi
    this->frontLeftLeg->pose(90, -90);
    this->frontRightLeg->pose(90, -90);
    this->backLeftLeg->pose(-90, -90);
    this->backRightLeg->pose(-90, -90);
}

MiniKame::~MiniKame()
{
    delete this->frontLeftLeg;
    delete this->frontRightLeg;
    delete this->backLeftLeg;
    delete this->backRightLeg;
}
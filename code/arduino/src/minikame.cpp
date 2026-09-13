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

void MiniKame::just_strafe_left()
{
    Gait frontLeftGait = Gaits::steadyGait(0, Gait::BACKWARD);
    frontLeftGait.position.spread = 60;
    this->frontLeftLeg->walk(frontLeftGait);
    Gait frontRightGait = Gaits::steadyGait(180, Gait::FORWARD);
    frontRightGait.position.spread = 60;
    this->frontRightLeg->walk(frontRightGait);
    Gait backLeftGait = Gaits::steadyGait(180, Gait::FORWARD);
    backLeftGait.position.spread = -50;
    this->backLeftLeg->walk(backLeftGait);
    Gait backRightGait = Gaits::steadyGait(0, Gait::BACKWARD);
    backRightGait.position.spread = -50;
    this->backRightLeg->walk(backRightGait);
}

void MiniKame::just_strafe_right()
{
    Gait frontLeftGait = Gaits::steadyGait(0, Gait::FORWARD);
    frontLeftGait.position.spread = 60;
    this->frontLeftLeg->walk(frontLeftGait);
    Gait frontRightGait = Gaits::steadyGait(180, Gait::BACKWARD);
    frontRightGait.position.spread = 60;
    this->frontRightLeg->walk(frontRightGait);
    Gait backLeftGait = Gaits::steadyGait(180, Gait::BACKWARD);
    backLeftGait.position.spread = -50;
    this->backLeftLeg->walk(backLeftGait);
    Gait backRightGait = Gaits::steadyGait(0, Gait::FORWARD);
    backRightGait.position.spread = -50;
    this->backRightLeg->walk(backRightGait);
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

void MiniKame::just_pack() {
    this->frontLeftLeg->pose(90, -90);
    this->frontRightLeg->pose(90, -90);
    this->backLeftLeg->pose(-90, -90);
    this->backRightLeg->pose(-90, -90);
}

void MiniKame::magic() {
    just_strafe_right();
}

void MiniKame::just_turn_in_place(bool left) {
    if (left) {
        just_left();
    } else {
        just_right();
    }
}

void MiniKame::just_crawl() {
    Gait crawlGait = Gaits::steadyGait(0, Gait::FORWARD);
    crawlGait.period = 2000;
    crawlGait.position.height = 35;
    this->frontLeftLeg->walk(crawlGait);
    crawlGait.phase = 180;
    this->frontRightLeg->walk(crawlGait);
    this->backLeftLeg->walk(crawlGait);
    crawlGait.phase = 0;
    this->backRightLeg->walk(crawlGait);
}

void MiniKame::just_tiptoe() {
    Gait tiptoeGait = Gaits::steadyShortGait(0, Gait::FORWARD);
    tiptoeGait.position.height = -35;
    this->frontLeftLeg->walk(tiptoeGait);
    tiptoeGait.phase = 180;
    this->frontRightLeg->walk(tiptoeGait);
    this->backLeftLeg->walk(tiptoeGait);
    tiptoeGait.phase = 0;
    this->backRightLeg->walk(tiptoeGait);
}

void MiniKame::just_recover() {
    Pair extreme = Pair(40, 40);
    this->frontLeftLeg->flex(300, 80, 0, extreme);
    this->frontRightLeg->flex(300, 80, 180, extreme);
    this->backLeftLeg->flex(300, 80, 180, extreme);
    this->backRightLeg->flex(300, 80, 0, extreme);
}

void MiniKame::just_sit() {
    this->frontLeftLeg->pose(0, -35);
    this->frontRightLeg->pose(0, -35);
    this->backLeftLeg->pose(-20, 50);
    this->backRightLeg->pose(20, 50);
}

void MiniKame::just_play_dead() {
    this->frontLeftLeg->pose(60, 55);
    this->frontRightLeg->pose(60, 55);
    this->backLeftLeg->pose(-60, 55);
    this->backRightLeg->pose(-60, 55);
}

void MiniKame::just_shiver() {
    Pair neutral = Pair(0, 0);
    this->frontLeftLeg->flex(100, 10, 0, neutral);
    this->frontRightLeg->flex(100, 10, 0, neutral);
    this->backLeftLeg->flex(100, 10, 0, neutral);
    this->backRightLeg->flex(100, 10, 0, neutral);
}

void MiniKame::just_scratch_ear() {
    this->backLeftLeg->pose(-25, 50);
    this->backRightLeg->pose(25, 50);
    this->frontRightLeg->pose(35, -40);
    this->frontLeftLeg->flex(150, 30, 0, Pair(45, 65));
}

void MiniKame::just_pounce_prep() {
    this->frontLeftLeg->pose(15, 45);
    this->frontRightLeg->pose(15, 45);
    Pair wiggle = Pair(0, -30);
    this->backLeftLeg->flex(250, 15, 0, wiggle);
    this->backRightLeg->flex(250, 15, 180, wiggle);
}

void MiniKame::just_wave_goodbye() {
    just_say_hi();
}

void MiniKame::just_tap_foot() {
    this->frontLeftLeg->pose(40, -35);
    this->backLeftLeg->pose(-20, -20);
    this->backRightLeg->pose(20, -25);
    this->frontRightLeg->flex(300, 25, 0, Pair(20, 25));
}

MiniKame::~MiniKame()
{
    delete this->frontLeftLeg;
    delete this->frontRightLeg;
    delete this->backLeftLeg;
    delete this->backRightLeg;
}
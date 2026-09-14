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

// ----------------------------------------------------------------------------
// Data-Driven MoveSpec Execution Engine
// ----------------------------------------------------------------------------

void MiniKame::applyLegSpec(Leg2DOF* leg, const LegSpec& spec) {
    if (!leg) return;
    switch (spec.mode) {
        case LegMode::POSE:
            leg->pose(spec.pose.spread, spec.pose.height);
            break;
        case LegMode::FLEX:
            leg->flex(spec.flex.period, spec.flex.amplitude, spec.flex.phase, spec.flex.position);
            break;
        case LegMode::WALK:
            leg->walk(spec.gait);
            break;
    }
}

void MiniKame::applySpec(const MoveSpec& spec) {
    applyLegSpec(this->frontLeftLeg, spec.fl);
    applyLegSpec(this->frontRightLeg, spec.fr);
    applyLegSpec(this->backLeftLeg, spec.bl);
    applyLegSpec(this->backRightLeg, spec.br);
}

bool MiniKame::executeMove(const String& name) {
    const MoveSpec* spec = MoveRegistry::find(name);
    if (spec) {
        applySpec(*spec);
        return true;
    }
    return false;
}

// ----------------------------------------------------------------------------
// Delegated Public Methods (Full Backward Compatibility)
// ----------------------------------------------------------------------------

void MiniKame::just_relax()        { executeMove("stop"); }
void MiniKame::just_walk()         { executeMove("run"); }
void MiniKame::just_back()         { executeMove("back"); }
void MiniKame::just_left()         { executeMove("turnL"); }
void MiniKame::just_right()        { executeMove("turnR"); }
void MiniKame::just_dance()        { executeMove("dance"); }
void MiniKame::just_upLeft()       { executeMove("upLeft"); }
void MiniKame::just_upRight()      { executeMove("upRight"); }
void MiniKame::just_backLeft()     { executeMove("backLeft"); }
void MiniKame::just_backRight()    { executeMove("backRight"); }
void MiniKame::just_jiggle()       { executeMove("jiggle"); }
void MiniKame::just_confused()     { executeMove("confused"); }
void MiniKame::just_pushUps()      { executeMove("pushUps"); }
void MiniKame::just_moonwalk()     { executeMove("moonWalk"); }
void MiniKame::just_stretch()      { executeMove("stretch"); }
void MiniKame::just_say_hi()       { executeMove("sayHi"); }
void MiniKame::just_pack()         { executeMove("pack"); }
void MiniKame::just_strafe_left()  { executeMove("strafeLeft"); }
void MiniKame::just_strafe_right() { executeMove("strafeRight"); }
void MiniKame::magic()             { executeMove("magic"); }
void MiniKame::just_turn_in_place(bool left) { executeMove(left ? "turnInPlaceL" : "turnInPlaceR"); }
void MiniKame::just_crawl()        { executeMove("crawl"); }
void MiniKame::just_tiptoe()       { executeMove("tiptoe"); }
void MiniKame::just_recover()      { executeMove("recover"); }
void MiniKame::just_sit()          { executeMove("sit"); }
void MiniKame::just_play_dead()    { executeMove("playDead"); }
void MiniKame::just_shiver()       { executeMove("shiver"); }
void MiniKame::just_scratch_ear()  { executeMove("scratchEar"); }
void MiniKame::just_pounce_prep()  { executeMove("pouncePrep"); }
void MiniKame::just_wave_goodbye() { executeMove("waveGoodbye"); }
void MiniKame::just_tap_foot()     { executeMove("tapFoot"); }

MiniKame::~MiniKame()
{
    delete this->frontLeftLeg;
    delete this->frontRightLeg;
    delete this->backLeftLeg;
    delete this->backRightLeg;
}
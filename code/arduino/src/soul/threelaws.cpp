#include "threelaws.h"

/*
 * First Law
 *      A robot may not injure a human being or, through inaction, allow a human being to come to harm.
 * Second Law
 *      A robot must obey the orders given it by human beings except where such orders would conflict with the First Law.
 * Third Law
 *      A robot must protect its own existence as long as such protection does not conflict with the First or Second Law.
 */

bool ThreeLawsOfRobotics::makesHarm() {
    // As to our best knowledge this action does not make harm
    bool makesHarm = false;
    return makesHarm;
}
bool ThreeLawsOfRobotics::preventsHarm() {
    // As to our best knowledge this action does not explicitly prevent harm
    bool preventsHarm = false;
    return preventsHarm;
}
bool ThreeLawsOfRobotics::obeysDirectOrder() {
    // As to our best knowledge this action does not obey a specific order
    bool obeys = false;
    return obeys;
}
bool ThreeLawsOfRobotics::disobeysDirectOrder() {
    // As to our best knowledge this action does not disobey a specific order
    bool disobeys = false;
    return disobeys;
}
bool ThreeLawsOfRobotics::makesSelfHarm() {
    // As to our best knowledge this action does not endanger the robot
    bool harmsSelf = false;
    return harmsSelf;
}
bool ThreeLawsOfRobotics::preventsSelfHarm() {
    // As to our best knowledge this action does not save the robot from danger
    bool protectsSelf = false;
    return protectsSelf;
}

bool ThreeLawsOfRobotics::conforms() {
    if (makesHarm()) {
        return false;
    }

    if (preventsHarm()) {
        return true;
    }

    if (obeysDirectOrder()) {
        return true;
    };
    
    if (disobeysDirectOrder()) {
        return false;
    }

    if (makesSelfHarm()) {
        return false;
    }

    // Currently useless, we keep it for case tracking if AI expands
    if (preventsSelfHarm()) {
        return true;
    }

    // can proceed with action
    return true;
}
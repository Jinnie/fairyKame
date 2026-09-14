#include "movespec.h"

// ----------------------------------------------------------------------------
// Static Move Specification Table
// ----------------------------------------------------------------------------
static const MoveSpec MOVE_SPECS[] = {
    // Neutral Stop / Relax
    {
        "stop",
        LegSpec::Pose(0, 0),
        LegSpec::Pose(0, 0),
        LegSpec::Pose(0, 0),
        LegSpec::Pose(0, 0)
    },
    {
        "relax",
        LegSpec::Pose(0, 0),
        LegSpec::Pose(0, 0),
        LegSpec::Pose(0, 0),
        LegSpec::Pose(0, 0)
    },

    // Standard Locomotion (700ms period, 20x20 amp)
    {
        "run",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false)
    },
    {
        "back",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true)
    },
    {
        "turnL",
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false)
    },
    {
        "turnInPlaceL",
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false)
    },
    {
        "turnR",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true)
    },
    {
        "turnInPlaceR",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true)
    },

    // Diagonals (using steadyShortGait: 5x20 amp)
    {
        "upLeft",
        LegSpec::Walk(700, 5, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false),
        LegSpec::Walk(700, 5, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false)
    },
    {
        "upRight",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 5, 20, 180, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 5, 20, 180, 0, 0, false)
    },
    {
        "backLeft",
        LegSpec::Walk(700, 5, 20, 0, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 5, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true)
    },
    {
        "backRight",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true),
        LegSpec::Walk(700, 5, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, true),
        LegSpec::Walk(700, 5, 20, 0, 0, 0, true)
    },

    // Lateral Strafing
    {
        "strafeLeft",
        LegSpec::Walk(700, 20, 20, 0, 60, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 60, 0, false),
        LegSpec::Walk(700, 20, 20, 180, -50, 0, false),
        LegSpec::Walk(700, 20, 20, 0, -50, 0, true)
    },
    {
        "strafeRight",
        LegSpec::Walk(700, 20, 20, 0, 60, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 60, 0, true),
        LegSpec::Walk(700, 20, 20, 180, -50, 0, true),
        LegSpec::Walk(700, 20, 20, 0, -50, 0, false)
    },
    {
        "magic",
        LegSpec::Walk(700, 20, 20, 0, 60, 0, false),
        LegSpec::Walk(700, 20, 20, 180, 60, 0, true),
        LegSpec::Walk(700, 20, 20, 180, -50, 0, true),
        LegSpec::Walk(700, 20, 20, 0, -50, 0, false)
    },

    // Specialized Locomotion
    {
        "crawl",
        LegSpec::Walk(2000, 20, 20, 0, 0, 35, false),
        LegSpec::Walk(2000, 20, 20, 180, 0, 35, false),
        LegSpec::Walk(2000, 20, 20, 180, 0, 35, false),
        LegSpec::Walk(2000, 20, 20, 0, 0, 35, false)
    },
    {
        "tiptoe",
        LegSpec::Walk(700, 5, 20, 0, 0, -35, false),
        LegSpec::Walk(700, 5, 20, 180, 0, -35, false),
        LegSpec::Walk(700, 5, 20, 180, 0, -35, false),
        LegSpec::Walk(700, 5, 20, 0, 0, -35, false)
    },

    // Expressive Gestures & Dances
    {
        "dance",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, true),
        LegSpec::Walk(700, 20, 20, 180, 0, 0, false)
    },
    {
        "jiggle",
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false),
        LegSpec::Walk(700, 20, 20, 0, 0, 0, false)
    },
    {
        "confused",
        LegSpec::Flex(200, 15, 0, 0, 60),
        LegSpec::Flex(200, 15, 0, 0, 60),
        LegSpec::Flex(200, 15, 0, 0, 60),
        LegSpec::Flex(200, 15, 0, 0, 60)
    },
    {
        "pushUps",
        LegSpec::Flex(1400, 65, 0, -10, -30),
        LegSpec::Flex(1400, 65, 0, -10, -30),
        LegSpec::Pose(-90, -30),
        LegSpec::Pose(-90, -30)
    },
    {
        "moonWalk",
        LegSpec::Flex(2000, 45, 0, -20, 30),
        LegSpec::Flex(2000, 45, 120, -20, 30),
        LegSpec::Flex(2000, 45, 0, 20, 30),
        LegSpec::Flex(2000, 45, 120, 20, 30)
    },
    {
        "stretch",
        LegSpec::Flex(2000, 45, 0, 0, -20),
        LegSpec::Flex(2000, 45, 120, 0, -20),
        LegSpec::Flex(2000, 45, 180, 0, -20),
        LegSpec::Flex(2000, 45, 290, 0, -20)
    },
    {
        "sayHi",
        LegSpec::Pose(50, -40),
        LegSpec::Flex(300, 30, 0, 60, 60),
        LegSpec::Pose(-50, 50),
        LegSpec::Pose(20, -25)
    },
    {
        "waveGoodbye",
        LegSpec::Pose(50, -40),
        LegSpec::Flex(300, 30, 0, 60, 60),
        LegSpec::Pose(-50, 50),
        LegSpec::Pose(20, -25)
    },
    {
        "scratchEar",
        LegSpec::Flex(150, 30, 0, 45, 65),
        LegSpec::Pose(35, -40),
        LegSpec::Pose(-25, 50),
        LegSpec::Pose(25, 50)
    },
    {
        "pouncePrep",
        LegSpec::Pose(15, 45),
        LegSpec::Pose(15, 45),
        LegSpec::Flex(250, 15, 0, 0, -30),
        LegSpec::Flex(250, 15, 180, 0, -30)
    },
    {
        "tapFoot",
        LegSpec::Pose(40, -35),
        LegSpec::Flex(300, 25, 0, 20, 25),
        LegSpec::Pose(-20, -20),
        LegSpec::Pose(20, -25)
    },
    {
        "recover",
        LegSpec::Flex(300, 80, 0, 40, 40),
        LegSpec::Flex(300, 80, 180, 40, 40),
        LegSpec::Flex(300, 80, 180, 40, 40),
        LegSpec::Flex(300, 80, 0, 40, 40)
    },
    {
        "shiver",
        LegSpec::Flex(100, 10, 0, 0, 0),
        LegSpec::Flex(100, 10, 0, 0, 0),
        LegSpec::Flex(100, 10, 0, 0, 0),
        LegSpec::Flex(100, 10, 0, 0, 0)
    },

    // Static Postures
    {
        "sit",
        LegSpec::Pose(0, -35),
        LegSpec::Pose(0, -35),
        LegSpec::Pose(-20, 50),
        LegSpec::Pose(20, 50)
    },
    {
        "playDead",
        LegSpec::Pose(60, 55),
        LegSpec::Pose(60, 55),
        LegSpec::Pose(-60, 55),
        LegSpec::Pose(-60, 55)
    },
    {
        "pack",
        LegSpec::Pose(90, -90),
        LegSpec::Pose(90, -90),
        LegSpec::Pose(-90, -90),
        LegSpec::Pose(-90, -90)
    }
};

static const size_t MOVE_SPEC_COUNT = sizeof(MOVE_SPECS) / sizeof(MOVE_SPECS[0]);

const MoveSpec* MoveRegistry::find(const String& name) {
    for (size_t i = 0; i < MOVE_SPEC_COUNT; i++) {
        if (name.equalsIgnoreCase(MOVE_SPECS[i].name)) {
            return &MOVE_SPECS[i];
        }
    }
    return nullptr;
}

const MoveSpec* MoveRegistry::getAll(size_t& count) {
    count = MOVE_SPEC_COUNT;
    return MOVE_SPECS;
}

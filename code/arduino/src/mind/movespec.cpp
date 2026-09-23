#include "movespec.h"

// ----------------------------------------------------------------------------
// Expressive, Object-Oriented Move Specification Table
// ----------------------------------------------------------------------------
static const MoveSpec MOVE_SPECS[] = {
    // ------------------------------------------------------------------------
    // Neutral Stop / Relax
    // ------------------------------------------------------------------------
    MoveSpec("stop", Pair(0, 0)),
    MoveSpec("relax", Pair(0, 0)),

    // ------------------------------------------------------------------------
    // Standard Locomotion (Gaits::steadyGait)
    // ------------------------------------------------------------------------
    MoveSpec("run",
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(180, Gait::FORWARD),
        Gaits::steadyGait(180, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::FORWARD)
    ),
    MoveSpec("back",
        Gaits::steadyGait(0, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyGait(0, Gait::BACKWARD)
    ),
    MoveSpec("turnL",
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::FORWARD)
    ),
    MoveSpec("turnInPlaceL",
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::FORWARD)
    ),
    MoveSpec("turnR",
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::BACKWARD)
    ),
    MoveSpec("turnInPlaceR",
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::BACKWARD)
    ),

    // ------------------------------------------------------------------------
    // Diagonal Locomotion (Gaits::steadyShortGait)
    // ------------------------------------------------------------------------
    MoveSpec("upLeft",
        Gaits::steadyShortGait(0, Gait::FORWARD),
        Gaits::steadyGait(180, Gait::FORWARD),
        Gaits::steadyShortGait(180, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::FORWARD)
    ),
    MoveSpec("upRight",
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyShortGait(180, Gait::FORWARD),
        Gaits::steadyGait(180, Gait::FORWARD),
        Gaits::steadyShortGait(0, Gait::FORWARD)
    ),
    MoveSpec("backLeft",
        Gaits::steadyShortGait(0, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyShortGait(180, Gait::BACKWARD),
        Gaits::steadyGait(0, Gait::BACKWARD)
    ),
    MoveSpec("backRight",
        Gaits::steadyGait(0, Gait::BACKWARD),
        Gaits::steadyShortGait(180, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::BACKWARD),
        Gaits::steadyShortGait(0, Gait::BACKWARD)
    ),

    // ------------------------------------------------------------------------
    // Lateral Strafing (Spread Offsets)
    // ------------------------------------------------------------------------
    MoveSpec("strafeLeft",
        Gaits::steadyGait(0, Gait::BACKWARD).withSpread(60),
        Gaits::steadyGait(180, Gait::FORWARD).withSpread(60),
        Gaits::steadyGait(180, Gait::FORWARD).withSpread(-50),
        Gaits::steadyGait(0, Gait::BACKWARD).withSpread(-50)
    ),
    MoveSpec("strafeRight",
        Gaits::steadyGait(0, Gait::FORWARD).withSpread(60),
        Gaits::steadyGait(180, Gait::BACKWARD).withSpread(60),
        Gaits::steadyGait(180, Gait::BACKWARD).withSpread(-50),
        Gaits::steadyGait(0, Gait::FORWARD).withSpread(-50)
    ),
    MoveSpec("magic",
        Gaits::steadyGait(0, Gait::FORWARD).withSpread(60),
        Gaits::steadyGait(180, Gait::BACKWARD).withSpread(60),
        Gaits::steadyGait(180, Gait::BACKWARD).withSpread(-50),
        Gaits::steadyGait(0, Gait::FORWARD).withSpread(-50)
    ),

    // ------------------------------------------------------------------------
    // Profile Walk Variations (Crawl & Tiptoe)
    // ------------------------------------------------------------------------
    MoveSpec("crawl",
        Gaits::steadyGait(0, Gait::FORWARD).withPeriod(2000).withHeight(35),
        Gaits::steadyGait(180, Gait::FORWARD).withPeriod(2000).withHeight(35),
        Gaits::steadyGait(180, Gait::FORWARD).withPeriod(2000).withHeight(35),
        Gaits::steadyGait(0, Gait::FORWARD).withPeriod(2000).withHeight(35)
    ),
    MoveSpec("tiptoe",
        Gaits::steadyShortGait(0, Gait::FORWARD).withHeight(-35),
        Gaits::steadyShortGait(180, Gait::FORWARD).withHeight(-35),
        Gaits::steadyShortGait(180, Gait::FORWARD).withHeight(-35),
        Gaits::steadyShortGait(0, Gait::FORWARD).withHeight(-35)
    ),

    // ------------------------------------------------------------------------
    // Expressive Rhythmic Gaits (Dance & Jiggle)
    // ------------------------------------------------------------------------
    MoveSpec("dance",
        Gaits::steadyGait(0, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::BACKWARD),
        Gaits::steadyGait(180, Gait::FORWARD)
    ),
    MoveSpec("jiggle",
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::FORWARD),
        Gaits::steadyGait(0, Gait::FORWARD)
    ),

    // ------------------------------------------------------------------------
    // Expressive Tricks (Flex Gestures)
    // ------------------------------------------------------------------------
    MoveSpec("confused",
        Flex(200, 15, 0, Pair(0, 60)),
        Flex(200, 15, 0, Pair(0, 60)),
        Flex(200, 15, 0, Pair(0, 60)),
        Flex(200, 15, 0, Pair(0, 60))
    ),
    MoveSpec("pushUps",
        Flex(1400, 65, 0, Pair(-10, -30)),
        Flex(1400, 65, 0, Pair(-10, -30)),
        Pair(-90, -30),
        Pair(-90, -30)
    ),
    MoveSpec("moonWalk",
        Flex(2000, 45, 0, Pair(-20, 30)),
        Flex(2000, 45, 120, Pair(-20, 30)),
        Flex(2000, 45, 0, Pair(20, 30)),
        Flex(2000, 45, 120, Pair(20, 30))
    ),
    MoveSpec("stretch",
        Flex(2000, 45, 0, Pair(0, -20)),
        Flex(2000, 45, 120, Pair(0, -20)),
        Flex(2000, 45, 180, Pair(0, -20)),
        Flex(2000, 45, 290, Pair(0, -20))
    ),
    MoveSpec("sayHi",
        Pair(50, -40),
        Flex(300, 30, 0, Pair(60, 60)),
        Pair(-50, 50),
        Pair(20, -25)
    ),
    MoveSpec("waveGoodbye",
        Pair(50, -40),
        Flex(300, 30, 0, Pair(60, 60)),
        Pair(-50, 50),
        Pair(20, -25)
    ),
    MoveSpec("recover",
        Flex(300, 80, 0, Pair(40, 40)),
        Flex(300, 80, 180, Pair(40, 40)),
        Flex(300, 80, 180, Pair(40, 40)),
        Flex(300, 80, 0, Pair(40, 40))
    ),
    MoveSpec("shiver",
        Flex(100, 10, 0, Pair(0, 0)),
        Flex(100, 10, 0, Pair(0, 0)),
        Flex(100, 10, 0, Pair(0, 0)),
        Flex(100, 10, 0, Pair(0, 0))
    ),
    MoveSpec("scratchEar",
        Flex(150, 30, 0, Pair(45, 65)),
        Pair(35, -40),
        Pair(-25, 50),
        Pair(25, 50)
    ),
    MoveSpec("pouncePrep",
        Pair(15, 45),
        Pair(15, 45),
        Flex(250, 15, 0, Pair(0, -30)),
        Flex(250, 15, 180, Pair(0, -30))
    ),
    MoveSpec("tapFoot",
        Pair(40, -35),
        Flex(300, 25, 0, Pair(20, 25)),
        Pair(-20, -20),
        Pair(20, -25)
    ),

    // ------------------------------------------------------------------------
    // Static Postures (Pair)
    // ------------------------------------------------------------------------
    MoveSpec("sit",
        Pair(0, -35),
        Pair(0, -35),
        Pair(-20, 50),
        Pair(20, 50)
    ),
    MoveSpec("playDead",
        Pair(60, 55),
        Pair(60, 55),
        Pair(-60, 55),
        Pair(-60, 55)
    ),
    MoveSpec("pack",
        Pair(90, -90),
        Pair(90, -90),
        Pair(-90, -90),
        Pair(-90, -90)
    )
};

static const size_t MOVE_SPECS_COUNT = sizeof(MOVE_SPECS) / sizeof(MOVE_SPECS[0]);

const MoveSpec* MoveRegistry::find(const String& name) {
    for (size_t i = 0; i < MOVE_SPECS_COUNT; ++i) {
        if (name.equalsIgnoreCase(MOVE_SPECS[i].name)) {
            return &MOVE_SPECS[i];
        }
    }
    return nullptr;
}

const MoveSpec* MoveRegistry::getAll(size_t& count) {
    count = MOVE_SPECS_COUNT;
    return MOVE_SPECS;
}

// ----------------------------------------------------------------------------
// Dynamic JSON Serialization & Deserialization
// ----------------------------------------------------------------------------
#include <ArduinoJson.h>

static LegSpec parseLegJson(JsonVariantConst v) {
    if (v.isNull()) {
        return LegSpec(Pair(0, 0));
    }

    // Array shortcut: [spread, height]
    if (v.is<JsonArrayConst>()) {
        JsonArrayConst arr = v.as<JsonArrayConst>();
        int s = arr.size() > 0 ? arr[0].as<int>() : 0;
        int h = arr.size() > 1 ? arr[1].as<int>() : 0;
        return LegSpec(Pair(s, h));
    }

    if (v.is<JsonObjectConst>()) {
        JsonObjectConst obj = v.as<JsonObjectConst>();
        String modeStr = obj["mode"] | "";
        modeStr.toLowerCase();

        // Check for Gait preset
        if (obj.containsKey("gait")) {
            String gName = obj["gait"] | "steady";
            int phase = obj["phase"] | 0;
            bool backward = obj["backward"] | false;
            String dirStr = obj["direction"] | "";
            if (dirStr.equalsIgnoreCase("backward") || dirStr.equalsIgnoreCase("back")) {
                backward = true;
            }

            Gait g;
            if (gName.indexOf("Short") >= 0 || gName.indexOf("short") >= 0) {
                g = Gaits::steadyShortGait(phase, backward);
            } else if (gName.indexOf("Rapid") >= 0 || gName.indexOf("rapid") >= 0) {
                g = Gaits::shortRapidGait(phase, backward);
            } else {
                g = Gaits::steadyGait(phase, backward);
            }

            if (obj.containsKey("period"))    g.period = obj["period"].as<int>();
            if (obj.containsKey("spread"))    g.position.spread = obj["spread"].as<int>();
            if (obj.containsKey("height"))    g.position.height = obj["height"].as<int>();
            if (obj.containsKey("ampSpread")) g.amplitude.spread = obj["ampSpread"].as<int>();
            if (obj.containsKey("ampHeight")) g.amplitude.height = obj["ampHeight"].as<int>();
            return LegSpec(g);
        }

        // Walk gait
        if (modeStr == "walk" || (obj.containsKey("ampSpread") && obj.containsKey("ampHeight"))) {
            int period    = obj["period"] | 700;
            int ampSpread = obj["ampSpread"] | 20;
            int ampHeight = obj["ampHeight"] | 20;
            int phase     = obj["phase"] | 0;
            int spread    = obj["spread"] | 0;
            int height    = obj["height"] | 0;
            bool backward = obj["backward"] | false;
            String dirStr = obj["direction"] | "";
            if (dirStr.equalsIgnoreCase("backward") || dirStr.equalsIgnoreCase("back")) {
                backward = true;
            }
            Gait g(period, Pair(ampSpread, ampHeight), phase, Pair(spread, height), backward);
            return LegSpec(g);
        }

        // Flex gesture
        if (modeStr == "flex" || (obj.containsKey("period") && obj.containsKey("amplitude"))) {
            int period = obj["period"] | 500;
            int amp    = obj["amplitude"] | 30;
            int phase  = obj["phase"] | 0;
            int spread = obj["spread"] | 0;
            int height = obj["height"] | 0;
            return LegSpec(Flex(period, amp, phase, Pair(spread, height)));
        }

        // Static pose (default)
        int spread = obj["spread"] | 0;
        int height = obj["height"] | 0;
        return LegSpec(Pair(spread, height));
    }

    return LegSpec(Pair(0, 0));
}

bool MoveSpec::fromJson(const String& jsonStr, MoveSpec& outSpec) {
    DynamicJsonDocument doc(1536);
    DeserializationError err = deserializeJson(doc, jsonStr);
    if (err) {
        return false;
    }

    JsonObjectConst root = doc.as<JsonObjectConst>();
    outSpec.name = root["name"] | "custom";
    outSpec.fl = parseLegJson(root["fl"]);
    outSpec.fr = parseLegJson(root["fr"]);
    outSpec.bl = parseLegJson(root["bl"]);
    outSpec.br = parseLegJson(root["br"]);
    return true;
}

static void serializeLeg(JsonObject legObj, const LegSpec& leg) {
    switch (leg.mode) {
        case LegMode::POSE:
            legObj["mode"] = "pose";
            legObj["spread"] = leg.pose.spread;
            legObj["height"] = leg.pose.height;
            break;
        case LegMode::FLEX:
            legObj["mode"] = "flex";
            legObj["period"] = leg.flex.period;
            legObj["amplitude"] = leg.flex.amplitude;
            legObj["phase"] = leg.flex.phase;
            legObj["spread"] = leg.flex.position.spread;
            legObj["height"] = leg.flex.position.height;
            break;
        case LegMode::WALK:
            legObj["mode"] = "walk";
            legObj["period"] = leg.gait.period;
            legObj["ampSpread"] = leg.gait.amplitude.spread;
            legObj["ampHeight"] = leg.gait.amplitude.height;
            legObj["phase"] = leg.gait.phase;
            legObj["spread"] = leg.gait.position.spread;
            legObj["height"] = leg.gait.position.height;
            legObj["backward"] = leg.gait.direction;
            break;
    }
}

String MoveSpec::toJson(const MoveSpec& spec) {
    DynamicJsonDocument doc(1536);
    doc["name"] = spec.name;
    serializeLeg(doc.createNestedObject("fl"), spec.fl);
    serializeLeg(doc.createNestedObject("fr"), spec.fr);
    serializeLeg(doc.createNestedObject("bl"), spec.bl);
    serializeLeg(doc.createNestedObject("br"), spec.br);
    String output;
    serializeJson(doc, output);
    return output;
}


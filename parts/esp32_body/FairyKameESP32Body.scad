// ==============================================================================
// FairyKame Sci-Fi ESP32 Quadruped Robot Body
// Inspired by: fairyKame_scifi.jpg & Javier Isabel's Kame32 architecture
// Target Board: ESP32 DevKit (30-pin & 38-pin NodeMCU-32S compatible)
// Actuators: 4x SG90 / MG90S Micro Servos for Hip Joints
// Features: 
//   - Front Camera & Sensor Bay with Bezel, Lens Port, and Chin Shelf
//   - Faceted Sci-Fi Bolted Top Cover with Raised Plateau & "FAIRY-01" Badge Bed
//   - Dual Pin Header Combs for VCC & GND Power Bus (Next to Servo GPIOs)
//   - Independent Removable Lid: Legs stay mounted to chassis during service!
//   - 100% Compatible with existing 2-DOF legs (leftBracket.stl / rightBracket.stl)
// ==============================================================================

$fn = 50; // Curve facet resolution (use 60+ for production STL export)

// ------------------------------------------------------------------------------
// Model Render Selector:
// 0 = Complete Assembled View (Chassis + Lid + Hardware preview)
// 1 = Main Chassis Tub (Printable)
// 2 = Sci-Fi Top Cover Lid (Printable)
// 3 = Exploded Assembly View
// 4 = Cross-Section Cutaway View (Internal Inspection)
// 5 = Open Cabin View (Tub + Hardware Mockup, No Lid)
// ------------------------------------------------------------------------------
part = 0;
explode_distance = 35; // Spacing for exploded view (mm)

// ==============================================================================
// Parametric Dimensions
// ==============================================================================

// Outer Chassis Envelope
body_length     = 88.0; // Front-to-back length (mm)
body_width      = 74.0; // Left-to-right width (mm)
body_height     = 27.0; // Chassis tub height (matches 27.0mm bracket yoke clearance)
wall_thickness  = 2.4;  // Main structural wall thickness (mm)
floor_thickness = 2.4;  // Bottom floor thickness (mm)
corner_chamfer  = 9.0;  // 45-degree corner chamfer for leg clearance & sci-fi aesthetic

// Servo Parameters (SG90 / MG90S)
servo_body_len  = 23.0; // Length of motor body (mm)
servo_body_wid  = 12.4; // Width of motor body (mm)
servo_body_hgt  = 22.8; // Height of motor body (mm)
servo_ear_len   = 4.8;  // Mounting ear length on each side (mm)
servo_shaft_off = 5.8;  // Distance from gear-end to shaft center (mm)
servo_shaft_dia = 5.0;  // Shaft collar / horn clearance diameter (mm)

// Hip Pivot / Shaft Coordinates (Symmetric 4 corners)
// Axis is vertically aligned between lower servo shaft and upper pivot anchor
shaft_x = body_width/2 - 8.5;    // ±28.5 mm from center
shaft_y = body_length/2 - 13.0;  // ±31.0 mm from center

// ESP32 DevKit Electronics Bay
esp32_len       = 55.0; // Max board length (NodeMCU-32S / DevKit v1)
esp32_wid       = 28.5; // Board width (mm)
esp32_standoff_h= 3.0;  // Standoff elevation above floor for bottom solder joints
esp32_usb_w     = 12.0; // Rear USB cutout width (mm)
esp32_usb_h     = 7.5;  // Rear USB cutout height (mm)

// Dual Power Pin Combs (VCC & GND Bus Rails for 8 Servos)
comb_length     = 25.4; // Length for 1x10 standard 2.54mm header strips (mm)
comb_slot_wid   = 2.6;  // Width of plastic header base slot (mm)
comb_slot_dep   = 2.5;  // Recess depth in floor for secure press-fit (mm)
comb_spacing    = 1.4;  // Gap between VCC and GND combs (mm)
comb_x_offset   = 15.2; // Placed between ESP32 (14.25mm) and servo inner wall (22.3mm)

// Front Camera & Sensor Bay (FairyKame Sci-Fi Styling)
cam_bay_w       = 32.0; // Recessed window width (mm)
cam_bay_h       = 14.0; // Recessed window height (mm)
cam_bay_depth   = 3.5;  // Recess depth into front face (mm)
cam_lens_dia    = 9.5;  // Camera lens / sensor aperture diameter (mm)
cam_wire_w      = 18.0; // Internal wire pass-through slot width (mm)
cam_wire_h      = 8.0;  // Internal wire pass-through slot height (mm)
cam_mount_pitch = 22.0; // M2 mounting screw hole pitch for camera board (mm)

// Top Cover Lid Parameters
lid_thickness   = 3.0;  // Base plate thickness of lid (mm)
lid_rim_h       = 2.5;  // Interlocking rim drop into tub (mm)
lid_rim_inset   = 1.0;  // Inset tolerance for easy slip fit (mm)
plateau_h       = 2.2;  // Raised faceted center plateau height (mm)
plateau_len     = 48.0; // Plateau length (mm)
plateau_wid     = 38.0; // Plateau width (mm)
badge_depth     = 0.6;  // Recessed "FAIRY-01" label emblem depth (mm)
bracket_corner_c= 15.0; // Corner chamfer cut on lid for bracket pivot swing clearance

// Fasteners & Hardware
screw_hole_d    = 3.2;  // M3 clearance through-hole (mm)
screw_head_d    = 6.2;  // M3 socket head counterbore diameter (mm)
screw_head_h    = 2.6;  // M3 socket head counterbore depth (mm)
boss_pilot_d    = 2.8;  // M3 pilot hole for self-tapping or brass heat-set insert (mm)
boss_od         = 7.2;  // Screw boss outer diameter (mm)
m3_nut_hex_d    = 6.3;  // M3 hex nut pocket diameter across points (mm)
m3_nut_hex_h    = 2.5;  // M3 hex nut pocket depth (mm)

// 4 Fastener Locations (Reinforced Internal Pillars)
screw_pos = [
    [ (body_width/2 - 6.0),  (body_length/2 - 25.0) ],
    [ -(body_width/2 - 6.0),  (body_length/2 - 25.0) ],
    [ (body_width/2 - 6.0), -(body_length/2 - 25.0) ],
    [ -(body_width/2 - 6.0), -(body_length/2 - 25.0) ]
];

// ==============================================================================
// 2D Profiles & Primitives
// ==============================================================================

// 8-Sided Faceted Profile (Chamfered Sci-Fi Silhouette)
module faceted_profile_2d(l, w, c) {
    polygon([
        [ -(w/2 - c),  l/2 ],
        [  (w/2 - c),  l/2 ],
        [  w/2,        (l/2 - c) ],
        [  w/2,       -(l/2 - c) ],
        [  (w/2 - c), -l/2 ],
        [ -(w/2 - c), -l/2 ],
        [ -w/2,       -(l/2 - c) ],
        [ -w/2,        (l/2 - c) ]
    ]);
}

// Extruded 3D Faceted Solid
module faceted_solid(l, w, h, c) {
    linear_extrude(height = h)
        faceted_profile_2d(l, w, c);
}

// ==============================================================================
// Sub-Assemblies & Cutouts
// ==============================================================================

// SG90 / MG90S Hip Servo Pocket Cutout
// (0, 0, 0) is the center of the output shaft at the chassis floor plane
module servo_pocket_cutout() {
    union() {
        // Output Shaft & Horn Collar Pass-Through on Floor
        translate([0, 0, -2])
            cylinder(d = servo_shaft_dia + 4.5, h = floor_thickness + 4);

        // Motor Main Body Cutout (Centered in X, extends in -Y towards waist)
        translate([-servo_body_wid/2, -(servo_body_len - servo_shaft_off), floor_thickness])
            cube([servo_body_wid, servo_body_len, servo_body_hgt + 2]);

        // Mounting Ears Shelf Cutout
        translate([-servo_body_wid/2, -(servo_body_len - servo_shaft_off + servo_ear_len), floor_thickness + 8.0])
            cube([servo_body_wid, servo_body_len + 2*servo_ear_len, 4.0]);

        // M2 Ear Screw Pilot Holes
        translate([0, servo_shaft_off + servo_ear_len/2, floor_thickness])
            cylinder(d = 1.8, h = 14);
        translate([0, -(servo_body_len - servo_shaft_off + servo_ear_len/2), floor_thickness])
            cylinder(d = 1.8, h = 14);

        // Internal Cable Pass-Through into Center Cabin
        translate([0, -(servo_body_len - servo_shaft_off), floor_thickness + 4.0])
            rotate([0, 0, 90])
            cube([6.0, 16.0, 5.0], center = true);
    }
}

// Upper Pivot Lug at Chassis Top (Matches Bracket Upper Hinge at Z=27.0mm)
module upper_pivot_anchors() {
    for (sx = [-1, 1]) {
        for (sy = [-1, 1]) {
            translate([sx * shaft_x, sy * shaft_y, 0]) {
                // M3 Pivot Through Hole
                translate([0, 0, -1])
                    cylinder(d = screw_hole_d, h = body_height + 2);

                // M3 Hex Nut Pocket on Underside of Top Ear
                translate([0, 0, body_height - 6.0])
                    cylinder(d = m3_nut_hex_d, h = m3_nut_hex_h + 0.5, $fn = 6);

                // Counterbore on Top Surface for Bushing/Spacer
                translate([0, 0, body_height - 1.2])
                    cylinder(d = 7.0, h = 2.0);
            }
        }
    }
}

// Front Camera Bay Opening (Sci-Fi Bezel, Lens Port, and Wire Routing)
module front_camera_bay() {
    translate([0, body_length/2 - cam_bay_depth, body_height/2 - 1.0]) {
        // Outer Recessed Bezel Window
        translate([-cam_bay_w/2, 0, -cam_bay_h/2])
            cube([cam_bay_w, cam_bay_depth + 2, cam_bay_h]);

        // Lower Beveled Chin (Hazard Stripe Shelf)
        translate([-cam_bay_w/2, 0, -cam_bay_h/2 - 1.5])
            rotate([30, 0, 0])
            cube([cam_bay_w, 3.5, 2.5]);

        // Circular Camera Lens Port
        rotate([-90, 0, 0])
            cylinder(d = cam_lens_dia, h = cam_bay_depth + wall_thickness + 4);

        // Internal Electronics Wire Pass-Through Window
        translate([-cam_wire_w/2, -wall_thickness - 2, -cam_wire_h/2])
            cube([cam_wire_w, wall_thickness + 4, cam_wire_h]);

        // 2x M2 Camera Board Mounting Screw Holes
        for (mx = [-cam_mount_pitch/2, cam_mount_pitch/2]) {
            translate([mx, -wall_thickness - 1, 0])
                rotate([-90, 0, 0])
                cylinder(d = 1.8, h = wall_thickness + 3);
        }
    }
}

// Dual Power Pin Combs (VCC and GND Rails)
module pin_comb_cutouts() {
    translate([comb_x_offset, -comb_length/2, floor_thickness - comb_slot_dep]) {
        // Comb 1: VCC Rail (+5V from BEC / Battery)
        cube([comb_slot_wid, comb_length, comb_slot_dep + 1]);

        // Comb 2: GND Rail (Common Ground)
        translate([comb_spacing + comb_slot_wid, 0, 0])
            cube([comb_slot_wid, comb_length, comb_slot_dep + 1]);

        // Under-Floor Power Lead Pass-Throughs
        translate([comb_slot_wid/2, 4.0, -floor_thickness])
            cylinder(d = 2.5, h = floor_thickness + 2);
        translate([comb_slot_wid + comb_spacing + comb_slot_wid/2, 4.0, -floor_thickness])
            cylinder(d = 2.5, h = floor_thickness + 2);
    }
}

// Rear USB Cutout (Micro-USB / USB-C Access)
module rear_usb_port() {
    translate([-esp32_usb_w/2, -body_length/2 - 1, floor_thickness + esp32_standoff_h + 1.0])
        cube([esp32_usb_w, wall_thickness + 3, esp32_usb_h]);
}

// Side Knee-Servo Wire Entry Slots (Left & Right Waist)
module side_wire_slots() {
    for (s = [-1, 1]) {
        translate([s * (body_width/2 - wall_thickness - 1), -4.0, body_height - 9.0])
            cube([wall_thickness + 3, 8.0, 5.0]);
    }
}

// ==============================================================================
// Module 1: Main Chassis Tub
// ==============================================================================
module chassis_tub() {
    difference() {
        union() {
            // Main Outer Faceted Body
            faceted_solid(body_length, body_width, body_height, corner_chamfer);

            // 4 Internal Reinforced Fastener Bosses
            for (p = screw_pos) {
                translate([p[0], p[1], 0])
                    cylinder(d = boss_od, h = body_height);
            }

            // 4 Corner Upper Pivot Reinforcement Lugs
            for (sx = [-1, 1]) {
                for (sy = [-1, 1]) {
                    translate([sx * shaft_x, sy * shaft_y, body_height - 6.0])
                        cylinder(d = 12.0, h = 6.0);
                }
            }

            // Central ESP32 Standoff Support Rails
            translate([-esp32_wid/2 - 1, -esp32_len/2, floor_thickness])
                cube([2.0, esp32_len, esp32_standoff_h]);
            translate([esp32_wid/2 - 1, -esp32_len/2, floor_thickness])
                cube([2.0, esp32_len, esp32_standoff_h]);
        }

        // Hollow Main Interior Cabin
        translate([0, 0, floor_thickness])
            faceted_solid(
                body_length - 2*wall_thickness,
                body_width - 2*wall_thickness,
                body_height + 2,
                corner_chamfer - wall_thickness
            );

        // 4 Hip Servo Pockets (at each corner, centered on shaft coordinates)
        // Front-Left (FL)
        translate([-shaft_x,  shaft_y, 0])
            servo_pocket_cutout();

        // Front-Right (FR)
        translate([shaft_x,  shaft_y, 0])
            servo_pocket_cutout();

        // Rear-Left (BL)
        translate([-shaft_x, -shaft_y, 0])
            rotate([0, 0, 180])
            servo_pocket_cutout();

        // Rear-Right (BR)
        translate([shaft_x, -shaft_y, 0])
            rotate([0, 0, 180])
            servo_pocket_cutout();

        // 4 Upper Pivot Lugs & Hex Nut Pockets
        upper_pivot_anchors();

        // Front Camera Bay
        front_camera_bay();

        // Rear USB Port
        rear_usb_port();

        // Dual Pin Header Combs for VCC & GND
        pin_comb_cutouts();

        // Side Cable Management Slots
        side_wire_slots();

        // 4 Screw Boss Pilot Holes for Lid Fasteners
        for (p = screw_pos) {
            translate([p[0], p[1], body_height - 14.0])
                cylinder(d = boss_pilot_d, h = 16.0);
        }

        // Top Mating Flange Inset (for Lid Rim Drop)
        translate([0, 0, body_height - lid_rim_h])
            faceted_solid(
                body_length - 2*(wall_thickness - lid_rim_inset),
                body_width - 2*(wall_thickness - lid_rim_inset),
                lid_rim_h + 1,
                corner_chamfer - (wall_thickness - lid_rim_inset)
            );
    }
}

// ==============================================================================
// Module 2: Sci-Fi Top Cover Lid
// ==============================================================================
module top_cover_lid() {
    difference() {
        union() {
            // Main Base Plate (with larger corner chamfer to clear leg bracket rotation)
            faceted_solid(body_length, body_width, lid_thickness, bracket_corner_c);

            // Interlocking Underside Rim (Drops into Tub)
            translate([0, 0, -lid_rim_h])
                faceted_solid(
                    body_length - 2*(wall_thickness + 0.4),
                    body_width - 2*(wall_thickness + 0.4),
                    lid_rim_h + 0.1,
                    corner_chamfer - (wall_thickness + 0.4)
                );

            // Raised Faceted Central Plateau (Sci-Fi Hatch)
            translate([0, 0, lid_thickness])
                faceted_solid(plateau_len, plateau_wid, plateau_h, 8.0);
        }

        // Recessed Badge Pocket on Central Plateau ("FAIRY-01" Decal Bed)
        translate([0, 0, lid_thickness + plateau_h - badge_depth])
            cube([plateau_wid - 8.0, plateau_len - 14.0, badge_depth + 1], center = true);

        // 4 Fastener Screw Holes with Counterbores (M3 Socket Head)
        for (p = screw_pos) {
            translate([p[0], p[1], -lid_rim_h - 1]) {
                // Through Hole
                cylinder(d = screw_hole_d, h = lid_thickness + plateau_h + 4);

                // Counterbore for Hex Socket Cap
                translate([0, 0, lid_rim_h + 1 + lid_thickness - screw_head_h])
                    cylinder(d = screw_head_d, h = screw_head_h + 2);
            }
        }

        // Underside Cavity for Top Clearance of ESP32 Components & Wires
        translate([0, 0, -lid_rim_h - 0.1])
            cube([esp32_wid + 4, esp32_len + 4, lid_rim_h - 0.8], center = true);
    }
}

// Realistic SG90 / MG90S Micro Servo Model
// (0, 0, 0) is the center of the output shaft at the floor_thickness plane
module sg90_servo_model() {
    color([0.15, 0.40, 0.85, 0.80]) // Translucent Blue SG90 Case
    union() {
        // Main Motor Body (Centered in X, extends in -Y towards waist)
        translate([-servo_body_wid/2, -(servo_body_len - servo_shaft_off), floor_thickness])
            cube([servo_body_wid, servo_body_len, servo_body_hgt]);

        // Mounting Ears Shelf
        translate([-servo_body_wid/2, -(servo_body_len - servo_shaft_off + servo_ear_len), floor_thickness + 8.0])
            cube([servo_body_wid, servo_body_len + 2*servo_ear_len, 2.5]);

        // Output Spline Shaft (pointing downward through the floor)
        color([0.9, 0.9, 0.9])
        translate([0, 0, -3.0])
            cylinder(d = servo_shaft_dia, h = floor_thickness + 3.0);

        // White Servo Horn (mockup below floor)
        color([0.95, 0.95, 0.95])
        translate([0, 0, -3.2])
            cylinder(d = 7.0, h = 1.2);
    }
}

// ==============================================================================
// Module 3: Hardware Mockup Preview (ESP32, Servos, Pin Combs)
// ==============================================================================
module hardware_preview() {
    // ESP32 DevKit Board Mockup (Classic Matte Black NodeMCU-32S)
    color([0.12, 0.12, 0.14, 0.95]) // Matte Black PCB
    translate([-esp32_wid/2, -esp32_len/2, floor_thickness + esp32_standoff_h]) {
        cube([esp32_wid, esp32_len, 1.6]);
        // Metal RF Shield
        color([0.85, 0.85, 0.88])
        translate([3, esp32_len - 22, 1.6])
            cube([18, 18, 2.8]);
        // Micro-USB / Type-C Port
        color([0.75, 0.75, 0.78])
        translate([esp32_wid/2 - 4.5, -2, 1.6])
            cube([9, 6, 3]);
    }

    // Dual Pin Header Combs Mockup (VCC = Red, GND = Black)
    translate([comb_x_offset, -comb_length/2, floor_thickness]) {
        // VCC Pin Strip (Red)
        color([0.9, 0.2, 0.2])
        cube([comb_slot_wid, comb_length, 7.5]);

        // GND Pin Strip (Black)
        translate([comb_spacing + comb_slot_wid, 0, 0])
        color([0.1, 0.1, 0.1])
        cube([comb_slot_wid, comb_length, 7.5]);
    }

    // 4x SG90 Hip Servos Mockup (Exact 1:1 match with chassis pockets)
    // Front-Left (FL)
    translate([-shaft_x,  shaft_y, 0])
        sg90_servo_model();

    // Front-Right (FR)
    translate([ shaft_x,  shaft_y, 0])
        sg90_servo_model();

    // Rear-Left (BL)
    translate([-shaft_x, -shaft_y, 0])
        rotate([0, 0, 180])
        sg90_servo_model();

    // Rear-Right (BR)
    translate([ shaft_x, -shaft_y, 0])
        rotate([0, 0, 180])
        sg90_servo_model();
}

// ==============================================================================
// Scene Composition & Render Logic
// ==============================================================================
if (part == 0) {
    // Complete Assembled View
    color([0.22, 0.23, 0.25]) // Dark Matte Graphite (Matching Sci-Fi Render)
        chassis_tub();

    color([0.28, 0.30, 0.33]) // Slightly Lighter Accent Lid
    translate([0, 0, body_height])
        top_cover_lid();

    // Hardware Preview Inside
    hardware_preview();

} else if (part == 1) {
    // Printable Chassis Tub
    chassis_tub();

} else if (part == 2) {
    // Printable Top Cover Lid (Oriented Flat for 3D Printing)
    rotate([180, 0, 0])
        top_cover_lid();

} else if (part == 3) {
    // Exploded Assembly View
    color([0.22, 0.23, 0.25])
        chassis_tub();

    hardware_preview();

    color([0.28, 0.30, 0.33])
    translate([0, 0, body_height + explode_distance])
        top_cover_lid();

} else if (part == 4) {
    // Cross-Section Cutaway View
    difference() {
        union() {
            chassis_tub();
            translate([0, 0, body_height]) top_cover_lid();
            hardware_preview();
        }
        // Cut away front-right quadrant
        translate([0, 0, -5])
            cube([body_width + 10, body_length + 10, body_height + 20]);
    }

} else if (part == 5) {
    // Open Cabin View (Chassis Tub + Hardware Mockup, No Lid)
    color([0.22, 0.23, 0.25])
        chassis_tub();

    hardware_preview();
}

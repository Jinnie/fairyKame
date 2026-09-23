// ==============================================================================
// FairyKame Modular Pinwheel Chassis Core
// 3-Layer Sandwich Structure for 4x Micro Servos (SG90 / FS90 / EMAX ES08MD)
// ==============================================================================

$fn = 50;

// Which layer to render:
// 1 = Bottom Layer (Base)
// 2 = Middle Layer (Clamp)
// 3 = Top Layer (Cap with Bearings/Pivots & Ventilation)
// 0 = Exploded 3-Layer Assembly View
layer = 0; 
explode_spacing = 25; // Vertical spacing (mm) in exploded view

// --- General Core Parameters ---
body_size = 50;             // 50x50 mm square body
corner_chamfer = 4.5;       // 4.5 mm corner chamfer on all layers for arm rotation clearance
m3_tab_d = 8;               // 8 mm diameter tab for M3 through-bolts
m3_hole_d = 3.2;            // 3.2 mm hole for M3 clearance
bevel_d = 9;                // 8 mm cylindrical counterbore diameter
bevel_depth = 2;            // 2 mm cylindrical counterbore depth

// --- Servo Dimensions & Tolerances ---
servo_len = 23;             // 23 mm motor body length
servo_wid = 12;             // 12 mm motor body width
padding = 5;                // 5 mm edge padding
ear_recess_depth = 3;       // 3 mm deep recess for ears in Layer 1
shaft_offset = 5.5;         // Distance from motor end to output shaft center

// --- Layer 1 (Bottom Plate) ---
l1_height = 6;              // 6 mm thickness
l1_well = 10;               // 10x10 mm center well

// --- Layer 2 (Middle Clamp Plate) ---
l2_height = 6;              // 6 mm thickness
l2_servo_len = 25;          // 25 mm cutout (1mm extra clearance each side)
l2_servo_wid = 14;          // 14 mm cutout (1mm extra clearance each side)
l2_well = 10;               // 10x10 mm center well

// --- Layer 3 (Top Cap) ---
l3_height = 5;              // 5 mm thickness
l3_well = 16;               // 16x16 mm center well
l3_well_r = 2;              // Corner radius for center well
pivot_hole_d = 3.2;         // 3.2 mm through-hole for M3 pivot screw (or 2.0 mm)
m3_nut_flats = 5.5;         // M3 nut flat-to-flat distance (5.5 mm)
m3_nut_r = (m3_nut_flats / cos(30)) / 2 + 0.15; // Point-to-point radius with 3D print tolerance
m3_nut_depth = 2.4;         // M3 nut recess depth (standard M3 nut is ~2.4 mm)
scallop_r = 8;              // Radius for inward edge scallops on top plate

// 4 Mid-edge bolt tab positions
m3_tab_positions = [
    [body_size / 2, body_size],     // Top edge center (25, 50)
    [body_size, body_size / 2],     // Right edge center (50, 25)
    [body_size / 2, 0],             // Bottom edge center (25, 0)
    [0, body_size / 2]              // Left edge center (0, 25)
];

// 4 Motor shaft centers opposite the top pivot
shaft_positions = [
    [45 - shaft_offset, 33 + servo_wid / 2],  // Top (Servo 1): (39.5, 39.0)
    [33 + servo_wid / 2, 5 + shaft_offset],   // Right (Servo 2): (39.0, 10.5)
    [5 + shaft_offset, 5 + servo_wid / 2],    // Bottom (Servo 3): (10.5, 11.0)
    [5 + servo_wid / 2, 45 - shaft_offset]    // Left (Servo 4): (11.0, 39.5)
];

// Helper: 2D base profile with 4 chamfered corners
module base_profile_2d() {
    c = corner_chamfer;
    polygon([
        [c, 0],
        [body_size - c, 0],
        [body_size, c],
        [body_size, body_size - c],
        [body_size - c, body_size],
        [c, body_size],
        [0, body_size - c],
        [0, c]
    ]);
}

// Helper: base plate with 4 chamfered corners and 4 mid-edge tabs
module base_slab(h) {
    union() {
        linear_extrude(height = h) base_profile_2d();
        for (pos = m3_tab_positions) {
            translate([pos[0], pos[1], 0])
                cylinder(d = m3_tab_d, h = h);
        }
    }
}

// Helper: 4 M3 through holes (extending 1mm beyond top and bottom)
module m3_through_holes(h) {
    for (pos = m3_tab_positions) {
        translate([pos[0], pos[1], -1])
            cylinder(d = m3_hole_d, h = h + 2);
    }
}

// ==============================================================================
// Layer 1: Bottom Base Plate (Chamfered corners + pinwheel servo cuts)
// ==============================================================================
module layer1() {
    difference() {
        // Base solid body
        base_slab(l1_height);

        // Center Well (10x10 mm) - 1mm extension top and bottom
        translate([(body_size - l1_well) / 2, (body_size - l1_well) / 2, -1])
            cube([l1_well, l1_well, l1_height + 2]);

        // 4 Servo Through-Cuts (12x23 mm) - 1mm extension top and bottom
        translate([22, 33, -1]) cube([servo_len, servo_wid, l1_height + 2]); // Top
        translate([33, 5, -1])  cube([servo_wid, servo_len, l1_height + 2]); // Right
        translate([5, 5, -1])   cube([servo_len, servo_wid, l1_height + 2]); // Bottom
        translate([5, 22, -1])  cube([servo_wid, servo_len, l1_height + 2]); // Left

        // 3 mm Deep Ear Recesses on inside face (Z = 3 to 7, extending 1mm above top face)
        // Servo 1 ears (along X)
        translate([16, 33, l1_height - ear_recess_depth]) cube([7, servo_wid, ear_recess_depth + 1]);
        translate([44, 33, l1_height - ear_recess_depth]) cube([7, servo_wid, ear_recess_depth + 1]);
        // Servo 2 ears (along Y)
        translate([33, -1, l1_height - ear_recess_depth]) cube([servo_wid, 7, ear_recess_depth + 1]);
        translate([33, 27, l1_height - ear_recess_depth]) cube([servo_wid, 7, ear_recess_depth + 1]);
        // Servo 3 ears (along X)
        translate([-1, 5, l1_height - ear_recess_depth])  cube([7, servo_wid, ear_recess_depth + 1]);
        translate([27, 5, l1_height - ear_recess_depth])  cube([7, servo_wid, ear_recess_depth + 1]);
        // Servo 4 ears (along Y)
        translate([5, 16, l1_height - ear_recess_depth])  cube([servo_wid, 7, ear_recess_depth + 1]);
        translate([5, 44, l1_height - ear_recess_depth])  cube([servo_wid, 7, ear_recess_depth + 1]);

        // 4 M3 through holes
        m3_through_holes(l1_height);

        // Cylindrical counterbores on bottom face (Z = -1 to 2)
        for (pos = m3_tab_positions) {
            translate([pos[0], pos[1], -1])
                cylinder(d = bevel_d, h = bevel_depth + 1);
        }
    }
}

// ==============================================================================
// Layer 2: Middle Clamp Plate (Chamfered corners + expanded 14x25 cuts)
// ==============================================================================
module layer2() {
    difference() {
        // Base solid body
        base_slab(l2_height);

        // Center Well (10x10 mm) - 1mm extension top and bottom
        translate([(body_size - l2_well) / 2, (body_size - l2_well) / 2, -1])
            cube([l2_well, l2_well, l2_height + 2]);

        // 4 Expanded Servo Through-Cuts (14x25 mm) - 1mm extension top and bottom
        translate([21, 32, -1]) cube([l2_servo_len, l2_servo_wid, l2_height + 2]); // Top
        translate([32, 4, -1])  cube([l2_servo_wid, l2_servo_len, l2_height + 2]); // Right
        translate([4, 4, -1])   cube([l2_servo_len, l2_servo_wid, l2_height + 2]); // Bottom
        translate([4, 21, -1])  cube([l2_servo_wid, l2_servo_len, l2_height + 2]); // Left

        // 4 M3 through holes
        m3_through_holes(l2_height);
    }
}

// ==============================================================================
// Layer 3: Top Cap (Chamfered corners + Ventilation Windows + Nut Pockets)
// ==============================================================================
module layer3() {
    difference() {
        // Base solid body
        base_slab(l3_height);

        // 16x16 mm Center Well with rounded corners - 1mm extension top and bottom
        translate([(body_size - l3_well) / 2, (body_size - l3_well) / 2, -1]) {
            hull() {
                translate([l3_well_r, l3_well_r, 0])
                    cylinder(r = l3_well_r, h = l3_height + 2);
                translate([l3_well - l3_well_r, l3_well_r, 0])
                    cylinder(r = l3_well_r, h = l3_height + 2);
                translate([l3_well - l3_well_r, l3_well - l3_well_r, 0])
                    cylinder(r = l3_well_r, h = l3_height + 2);
                translate([l3_well_r, l3_well - l3_well_r, 0])
                    cylinder(r = l3_well_r, h = l3_height + 2);
            }
        }

        // --- 4 Large Ventilation Windows over the Motor Bodies ---
        // Top window (over Servo 1 body)
        translate([20, 33.5, -1])
            hull() {
                translate([1.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([11.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([11.5, 9.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([1.5, 9.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
            }

        // Right window (over Servo 2 body)
        translate([33.5, 17, -1])
            hull() {
                translate([1.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([9.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([9.5, 11.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([1.5, 11.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
            }

        // Bottom window (over Servo 3 body)
        translate([17, 5.5, -1])
            hull() {
                translate([1.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([11.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([11.5, 9.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([1.5, 9.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
            }

        // Left window (over Servo 4 body)
        translate([5.5, 20, -1])
            hull() {
                translate([1.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([9.5, 1.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([9.5, 11.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
                translate([1.5, 11.5, 0]) cylinder(r = 1.5, h = l3_height + 2);
            }

        // 4 Pivot through-holes opposite the motor axes
        for (pos = shaft_positions) {
            translate([pos[0], pos[1], -1])
                cylinder(d = pivot_hole_d, h = l3_height + 2);

            // Hex cutout for M3 nut on the underside (Z = -1 to m3_nut_depth)
            translate([pos[0], pos[1], -1])
                cylinder(r = m3_nut_r, h = m3_nut_depth + 1, $fn = 6);
        }

        // 4 M3 through holes
        m3_through_holes(l3_height);

        // Cylindrical counterbores on top face (Z = l3_height - bevel_depth to l3_height + 1)
        for (pos = m3_tab_positions) {
            translate([pos[0], pos[1], l3_height - bevel_depth])
                cylinder(d = bevel_d, h = bevel_depth + 1);
        }
    }
}

// ==============================================================================
// Render Logic
// ==============================================================================
if (layer == 1) {
    layer1();
} else if (layer == 2) {
    layer2();
} else if (layer == 3) {
    layer3();
} else {
    // Exploded assembly view showing all 3 layers stacked
    color("darkgray") layer1();
    color("limegreen") translate([0, 0, l1_height + explode_spacing]) layer2();
    color("lightgreen") translate([0, 0, l1_height + l2_height + explode_spacing * 2]) layer3();
}

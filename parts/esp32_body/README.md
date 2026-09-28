# FairyKame ESP32 Sci-Fi Body Enclosure

## Overview

The **FairyKame ESP32 Body** is an updated chassis enclosure modeled directly after the sci-fi render ([`doc/images/fairyKame_scifi.jpg`](../../doc/images/fairyKame_scifi.jpg)) and informed by Javier Isabel's **Kame32** architecture.

It transitions FairyKame from the vintage NodeMCU ESP8266 to the more capable dual-core **ESP32 DevKit** while maintaining full mechanical backward compatibility with the existing 2-DOF leg assemblies ([`leftBracket.stl`](../stl/leftBracket.stl) and [`rightBracket.stl`](../stl/rightBracket.stl)).

---

## Key Features & Sci-Fi Aesthetics

1. **Front Camera & Sensor Bay:**
   - Recessed rectangular front window (`32 mm × 14 mm × 3.5 mm`) matching the sci-fi render.
   - Central circular aperture ($\varnothing 9.5\,\text{mm}$) sized for miniature FPV camera lenses, ESP32-CAM modules, or distance sensors (VL53L0X / Ultrasonic).
   - Beveled lower "chin" shelf (ideal placement for hazard stripe warning decals).
   - Internal wire pass-through window into the main electronics compartment.
   - Dual M2 mounting screw holes ($22\,\text{mm}$ pitch) for securing an internal camera PCB.

2. **Sci-Fi Faceted Top Cover Lid:**
   - 8-sided faceted profile with $45^\circ$ corner chamfers.
   - Raised central plateau ($48\,\text{mm} \times 38\,\text{mm} \times 2.2\,\text{mm}$) with a recessed badge pocket for the `"FAIRY-01"` decal.
   - Secured with 4× M3 socket head cap screws recessed into counterbores.
   - **Independent Serviceability:** The 4 leg brackets pivot directly on reinforced upper lugs of the chassis tub at $Z = 27\,\text{mm}$. The top lid can be removed at any time for electronics inspection or battery swaps **without disconnecting the leg pivots**.

3. **Dual Power Pin Combs (VCC & GND Bus Rails):**
   - Two recessed retention channels in the floor alongside the ESP32's servo GPIO pins.
   - Sized for standard $1 \times 10$ or $1 \times 8$ male pin header strips ($2.54\,\text{mm}$ pitch).
   - **Comb 1 (Red):** Common $+5\,\text{V}$ rail powered directly from an external BEC or battery regulator.
   - **Comb 2 (Black):** Common Ground rail connected to system ground.
   - Simplifies the 8 servo wire connections (4 hip servos + 4 knee servos) without needing a messy breadboard or custom PCB.

4. **Actuator & Board Compatibility:**
   - **Hip Servos:** 4× SG90 or metal-gear MG90S micro servos seated in dedicated corner pockets with M2 ear mounting tabs and bottom shaft pass-throughs.
   - **Microcontroller:** Fits standard 30-pin and 38-pin (NodeMCU-32S) ESP32 DevKit boards ($55\,\text{mm} \times 28.5\,\text{mm}$).
   - **Rear USB Port:** Integrated $12\,\text{mm} \times 7.5\,\text{mm}$ opening allowing USB flashing and serial monitoring without disassembling the robot.
   - **Leg Compatibility:** $27.0\,\text{mm}$ tub height and $\pm 28.5\,\text{mm} \times \pm 31.0\,\text{mm}$ pivot coordinates precisely match existing `leftBracket.stl` and `rightBracket.stl` yokes.

---

## File Structure

```text
parts/esp32_body/
├── README.md                     # This documentation
├── FairyKameESP32Body.scad       # Parametric OpenSCAD source model
├── FairyKameESP32_Chassis.stl   # Exported 3D-printable main tub
├── FairyKameESP32_Lid.stl       # Exported 3D-printable top cover
├── render_assembled_front.png   # Preview render of assembled robot body
└── render_exploded.png          # Preview render of exploded assembly
```

---

## OpenSCAD Configuration & Render Selector

Open [`FairyKameESP32Body.scad`](FairyKameESP32Body.scad) in OpenSCAD. The top of the file provides a `part` selector:

| `part` Value | Mode | Description |
| :---: | :--- | :--- |
| `0` | **Assembled View** | Complete chassis tub + top cover lid + hardware preview |
| `1` | **Chassis Tub** | Printable lower body box with servo sockets and electronics bay |
| `2` | **Top Cover Lid** | Printable top cover lid (oriented flat on the print bed) |
| `3` | **Exploded View** | Exploded perspective showing internal component stacking |
| `4` | **Cutaway View** | Cross-section view for internal clearance inspection |

### Exporting STLs via Command Line

```bash
# Render & export the main chassis tub:
openscad -o FairyKameESP32_Chassis.stl -D "part=1" FairyKameESP32Body.scad

# Render & export the top cover lid:
openscad -o FairyKameESP32_Lid.stl -D "part=2" FairyKameESP32Body.scad
```

---

## 3D Printing Recommendations

| Parameter | Recommended Setting |
| :--- | :--- |
| **Material** | PLA+, PETG, or ABS/ASA |
| **Layer Height** | $0.20\,\text{mm}$ (or $0.16\,\text{mm}$ for crisp chamfers) |
| **Perimeters / Walls** | 3 to 4 walls for rigid structural rigidity |
| **Infill** | 20% – 25% (Gyroid or Grid) |
| **Supports** | Required for the front camera bay opening and USB cutout; build plate only |
| **Orientation** | Print `Chassis Tub` upright on its flat bottom; print `Top Cover Lid` inverted (flat top on bed) |

# FairyKame MoveSpec Library

This directory houses the JSON specifications for custom FairyKame gaits, postures, and expressive movements.

FairyKame's **Spinal Cord Engine** parses these data-driven specifications over Wi-Fi (`POST /spec`) or USB Serial without requiring firmware recompilation.

---

## 1. Directory Contents

| File | Type | Description |
| :--- | :--- | :--- |
| [`atat_walker.json`](atat_walker.json) | Gait | Star Wars AT-AT Imperial Walker 4-beat crawling gait ($1600\text{ms}$ period, $-45^\circ$ tall stance, $90^\circ$ phase shifts). |
| [`seductive_sway.json`](seductive_sway.json) | Gesture | Slow, sultry $360^\circ$ circular hip roll with an undulating $2600\text{ms}$ rhythm. |
| [`neck_massage.json`](neck_massage.json) | Massage | Body-mounted neck & shoulder massage gait. Rear legs form a wide flat stabilizing kickstand while front paws perform deep 2-DOF alternating circular kneading. |
| [`neck_massage_tap.json`](neck_massage_tap.json) | Massage | Body-mounted deep shiatsu acupressure tapping rhythm ($360\text{ms}$ period, $24^\circ$ amplitude) with wide rear anchor. |
| [`chaplin_bread_dance.json`](chaplin_bread_dance.json) | Dance | Charlie Chaplin's 1925 "Oceana Roll" Bread Dance from *The Gold Rush*. Seated tabletop tap-dance waltz. |
| [`park_walk.json`](park_walk.json) | Locomotion | AI-synthesized 4-beat lateral sequence forward park walk ($1050\text{ms}$, $-35^\circ$ elevated stance, $3$-point static stability). |
| [`walk_back.json`](walk_back.json) | Locomotion | AI-synthesized 4-beat backward retreat crawl ($1050\text{ms}$, $-35^\circ$ elevated stance, reverse phasing). |
| [`turn_left.json`](turn_left.json) | Locomotion | AI-synthesized 4-beat differential arc turn left (outer full stride, inner compact pivot). |
| [`turn_right.json`](turn_right.json) | Locomotion | AI-synthesized 4-beat differential arc turn right (outer full stride, inner compact pivot). |
| [`spin_left.json`](spin_left.json) | Locomotion | AI-synthesized 4-beat zero-radius counter-clockwise pivot spin with continuous 3-point stability. |
| [`spin_right.json`](spin_right.json) | Locomotion | AI-synthesized 4-beat zero-radius clockwise pivot spin with continuous 3-point stability. |
| [`strafe_left.json`](strafe_left.json) | Locomotion | AI-synthesized 4-beat lateral crab walk left ($950\text{ms}$, $+65^\circ$ front splay, $-30^\circ$ rear neutral). |
| [`strafe_right.json`](strafe_right.json) | Locomotion | AI-synthesized 4-beat lateral crab walk right ($950\text{ms}$, $+65^\circ$ front splay, $-30^\circ$ rear neutral). |
| [`diagonal_up_left.json`](diagonal_up_left.json) | Locomotion | AI-synthesized 4-beat 45-degree forward-left diagonal locomotion. |
| [`diagonal_up_right.json`](diagonal_up_right.json) | Locomotion | AI-synthesized 4-beat 45-degree forward-right diagonal locomotion. |
| [`diagonal_back_left.json`](diagonal_back_left.json) | Locomotion | AI-synthesized 4-beat 45-degree backward-left diagonal retreat. |
| [`diagonal_back_right.json`](diagonal_back_right.json) | Locomotion | AI-synthesized 4-beat 45-degree backward-right diagonal retreat. |
| [`crawl_stealth.json`](crawl_stealth.json) | Locomotion | AI-synthesized low-profile tactical stealth prowl ($1350\text{ms}$, $-12^\circ$ height, $+45^\circ$ reach, suspended clearance). |
| [`tiptoe_stilt.json`](tiptoe_stilt.json) | Locomotion | AI-synthesized high-stilt alert march ($750\text{ms}$, $-65^\circ$ towering stance, high knee clearance). |

---

## 2. Playing a Spec File

Use the included helper script to send any spec file directly to FairyKame over Wi-Fi:

```bash
# Play a spec continuously:
python scripts/play_spec.py specs/atat_walker.json

# Play for a specific duration (e.g. 10 seconds), then automatically stop:
python scripts/play_spec.py specs/atat_walker.json --duration 10.0

# Emergency stop & relax:
python scripts/play_spec.py --stop
```

Or execute it directly via the AI Model Context Protocol (MCP) bridge using the `fairykame_custom_spec` tool.

---

## 3. MoveSpec JSON Specification Format

A MoveSpec defines the configuration of the 4 legs:
* `fl`: Front-Left
* `fr`: Front-Right
* `bl`: Back-Left
* `br`: Back-Right

Each leg supports three operating modes:

### A. Walk Mode (2-DOF Sinusoidal Walking)
```json
{
  "mode": "walk",
  "period": 1600,
  "ampSpread": 14,
  "ampHeight": 25,
  "phase": 90,
  "spread": 0,
  "height": -45,
  "direction": "forward"
}
```
* `period`: Oscillation cycle duration in milliseconds (e.g. $350\text{ms}$ = rapid sprint, $1600\text{ms}$ = heavy walk).
* `ampSpread`: Hip lateral swing amplitude in degrees ($\pm 90^\circ$).
* `ampHeight`: Knee vertical lift amplitude in degrees ($\pm 90^\circ$).
* `phase`: Starting phase offset in degrees ($0^\circ$ to $360^\circ$).
* `spread`: Static hip center offset in degrees.
* `height`: Static knee center offset in degrees (negative = taller stance; positive = squat).
* `direction`: `"forward"` or `"backward"`.

### B. Flex Mode (1-DOF Knee Oscillation)
```json
{
  "mode": "flex",
  "period": 400,
  "amplitude": 30,
  "phase": 0,
  "spread": 40,
  "height": 60
}
```

### C. Static Pose Mode
```json
{
  "mode": "pose",
  "spread": 20,
  "height": -40
}
```
*(Or compact array syntax: `[20, -40]`)*

---

## 4. Firmware Roadmap: Replacing Built-In Hardcoded Gaits

In future firmware releases (tracked in `TODO.md`), FairyKame will use **LittleFS / SPIFFS** flash storage:
1. Specs saved in `specs/` will be bundled into the microcontroller's filesystem.
2. The firmware will dynamically load moves by name from JSON files on flash rather than storing large static C++ structs in flash memory.
3. Users and AI agents will be able to upload, edit, or delete moves wirelessly over HTTP (`POST /specs/upload`).

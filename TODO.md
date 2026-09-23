# TODO & Roadmap

This document tracks planned improvements, architectural ideas, and technical debt for the **FairyKame** project.

---

## 1. Web Controller & Asset Pipeline
- [ ] **Eliminate HTML/C++ Duplication:**
  - *Option A (Pre-build Script):* Add a PlatformIO pre-build extra script (`extra_scripts = pre:bundle_html.py`) that reads `code/html/fatKameCommand.html`, minifies/escapes it, and generates a C++ header or embeds it into `webconnector.cpp` automatically at compile time.
  - *Option B (LittleFS / SPIFFS):* Store static HTML, CSS, and JS files directly in flash filesystem (LittleFS) and serve them using `ESP8266WebServer::serveStatic()`. This allows serving rich web interfaces without bloating the C++ binary.
  - *Option C (Single File Spec):* If embedding in C++ is kept as-is, decide whether to keep `fatKameCommand.html` strictly as a developer preview/template with an automated sync test or script.

---

## 2. Hardware & Servo Calibration
- [ ] **Independent Per-Leg Trimming:**
  - Currently `TRIM_HEIGHT` and `TRIM_SPREAD` in `leg-2dof.cpp` are hardcoded to `0` globally.
  - Implement independent calibration offsets for all 8 servos (Front-Left Hip/Knee, Front-Right Hip/Knee, Back-Left Hip/Knee, Back-Right Hip/Knee).
  - Persist calibration values in non-volatile memory (LittleFS, EEPROM, or ESP8266 Preferences) so mechanical zeroing does not require re-seating servo horns.
  - Expose a calibration mode or web endpoint (`/calibrate?leg=...&joint=...&offset=...`) to trim each joint interactively.

---

## 3. Gaits & Kinematics
- [ ] **Implement `shortRapidGait`:**
  - `Gaits::shortRapidGait` is currently declared in `gaits.h` but not implemented in `gaits.cpp`. Define suitable period, amplitude, and phase for rapid stepping.
- [ ] **Non-Circular Amplitudes:**
  - Explore asymmetrical step paths (different horizontal vs vertical amplitudes / elliptical trajectories) in `Leg2DOF::walk()`.
- [ ] **Smooth Gait Transitions:**
  - Smoothly interpolate between distinct gaits or poses to prevent abrupt jerk when switching active commands in `main.cpp`.
- [ ] **Inter-Leg Collision Avoidance & Spatial Safety Constraints:**
  - Prevent adjacent front and rear hips/legs from colliding when swinging past physical boundaries (e.g., front hip swinging backward beyond the $90^\circ$ perpendicular line at $\approx -30^\circ$, or rear hip swinging forward into the front leg's envelope).
  - Implement a mutual spatial clearance check in `Mind` / `Leg2DOF` / `ThreeLawsOfRobotics` before committing target angles to `Joint::setPosition()`, ensuring legs dynamically respect each other's physical boundaries.
- [ ] **Harmonic Knee Oscillation ($2\times$ Frequency):**
  - Implement support for harmonic vertical frequency (knee oscillating at $2\times$ hip stride frequency) inspired by `kame32`, producing crisp double-step ground clearance curves.
- [ ] **Dynamic Center-of-Mass (CoM) Pitch Shift (`body_shift`):**
  - Dynamically lean hip baselines forward during high acceleration/velocity ($\text{body\_shift} = \text{step\_amplitude} \times 0.8$) to counter inertia and prevent backward tipping (see [`doc/ECOSYSTEM_RESEARCH.md`](doc/ECOSYSTEM_RESEARCH.md)).

---

## 4. Architecture & Refactoring
- [ ] **Evaluate `CommandExecutor`:**
  - Currently `commandexecutor.cpp` uses a chain of `if-else` string comparisons. Evaluate replacing with a hash map / function pointer lookup table, or unifying command dispatch with `Mind`.
- [ ] **Loop Timing & Servo Frequency:**
  - Make oscillator step calculation (`pulse()`) strictly time-based rather than tied to `delay(Mind::getDelay())`.

---

## 5. Mobile & Connectivity (Stretch Goals)
- [ ] **Migration to ESP32 (Hardware Upgrade):**
  - Migrate firmware, pin configuration, and chassis mounts from ESP8266 (NodeMCU v2) to an ESP32 SoC (e.g. ESP32 DevKit / NodeMCU-32S).
  - Abstract pinouts and HAL to leverage ESP32 hardware PWM and power routing.
  - *Architectural Decision:* External Bluetooth adapters/modules (such as HC-05/HC-06/JDY-31) are explicitly ruled out; native on-chip ESP32 integration is the sole intended upgrade path.
- [ ] **Native Bluetooth Serial (SPP) Control:**
  - Leverage ESP32's built-in Bluetooth radio using `BluetoothSerial` (Serial Port Profile).
  - Pairs directly with host PCs as a wireless virtual COM port (`COMx`), enabling `scripts/gamepad_controller.py` to operate wirelessly with zero latency and without switching Wi-Fi networks.
- [ ] **Bluetooth Low Energy (BLE) & Mobile App:**
  - Add BLE GATT services for motion dispatch and telemetry.
  - Experiment with a lightweight cross-platform mobile app (e.g. React Native or Flutter) to steer FairyKame via a virtual joystick.

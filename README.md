# PID Line Follower — Precision, Balance, Flow

**A decorative, practical, and evolving build** of a line‑following robot that blends quick sensor logic with steady PID‑based motor control. The goal is simple: keep the robot centered, smooth, and confident—whether it’s cruising straight or carving sharp turns.

---

## ✨ Project Story
Line following produces a continuous stream of position error. PID turns that signal into disciplined motion so the robot doesn’t overreact to every wiggle in the line. In this project, the line‑follower logic and PID tuning **collaborate**: sensors decide direction, PID decides *how much* correction to apply.

$$u(t)=K_p e(t)+K_i\int e(t)\,dt+K_d\frac{de(t)}{dt}$$

- **$K_p$** responds to the current error (fast correction).
- **$K_i$** corrects long‑term bias (motor mismatch, surface drift).
- **$K_d$** damps oscillation (smoother corners, less overshoot).

---

## 🔧 Hardware Assumptions
- Arduino Nano (ATmega328P)
- Dual DC motors with an H‑bridge driver
- Quadrature encoders
- 3‑IR or 5‑IR reflectance sensor array

---

## 🧠 Control Strategy Overview
The robot uses **two layers** of reasoning:

1. **Line Detection Logic**: Interprets IR sensor states to decide direction.
2. **PID Motor Balancing**: Uses encoder feedback to maintain straightness and reduce drift.

This combo keeps the robot **agile in turns** and **stable on long straights**.

---

## 📁 Repository Map
### Main Program
- [src/main.cpp](src/main.cpp) — 3‑sensor line‑following loop with motor helpers and encoder wiring. It is the clean baseline and the foundation for the experiments.

### Experiments & Tuning
The [test](test) folder is a collection of focused sketches for calibration and tuning. These are standalone development files, not PlatformIO unit tests.

#### Line Following Variants
- [test/three_ir_working.cpp](test/three_ir_working.cpp) — Stable 3‑IR baseline logic.
- [test/five_ir_working.cpp](test/five_ir_working.cpp) — 5‑IR logic with sharper turn handling.
- [test/five_ir_test.cpp](test/five_ir_test.cpp) — Threshold‑comparison variant.
- [test/five_ir_smoothing.cpp](test/five_ir_smoothing.cpp) — Adds speed smoothing to reduce jerk.
- [test/line_follow_overshoot_tuning.cpp](test/line_follow_overshoot_tuning.cpp) — Overshoot mitigation experiments.

#### PID & Encoder Tuning
- [test/pid_straight_line.cpp](test/pid_straight_line.cpp) — Encoder PID loop to keep straight motion balanced.
- [test/pid_library_balance.cpp](test/pid_library_balance.cpp) — PID_v1 balancing baseline.
- [test/pid_library_tuning.cpp](test/pid_library_tuning.cpp) — Higher‑gain PID_v1 tuning tests.
- [test/encoder_forward_test.cc](test/encoder_forward_test.cc) — Minimal motor/encoder wiring sanity check.

#### Data & Utilities
- [test/matlab_sim_data.txt](test/matlab_sim_data.txt) — Logged values for MATLAB simulation and verification.
- [test/encodertestcodes/encoder_interrupt_read.ino](test/encodertestcodes/encoder_interrupt_read.ino) — Encoder interrupt reference.
- [test/MotorTest/nano_benchmark.ino](test/MotorTest/nano_benchmark.ino) — Arduino Nano CPU timing benchmark.

---

## 🎯 Tuning Notes
- Start with conservative $K_p$ and increase until mild oscillation appears, then back off.
- Add a small $K_d$ to smooth sharp turns and reduce overshoot.
- Use $K_i$ sparingly to avoid wind‑up and slow drift.

---

## 🧪 Build & Upload
This is a PlatformIO project. The active environment is defined in [platformio.ini](platformio.ini).

---

## ✅ Practical Tips
- Keep the motor direction conventions consistent across sketches.
- Re‑check encoder polarity after rewiring.
- Use one file at a time while tuning to avoid mixed assumptions.

---

If you extend the logic, keep the motor helper function consistent so behavior stays predictable across tests.
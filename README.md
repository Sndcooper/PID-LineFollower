# PID Line Follower (Arduino Nano)

This project is a compact, practical exploration of **PID control** applied to a **line‑following robot**. The core idea is to combine fast, reliable sensor feedback from IR reflectance sensors with a stable control loop that balances motor speeds and minimizes drift. The collaboration between the line‑follower logic and PID tuning is what makes the robot both responsive on sharp turns and calm on straight segments.

## Why PID for a Line Follower
Line following naturally produces an *error signal*—how far the robot is from the desired line. PID turns that error into smooth motor corrections:

$$u(t)=K_p e(t)+K_i\int e(t)\,dt+K_d\frac{de(t)}{dt}$$

- **$K_p$** reacts to current error (quick response).
- **$K_i$** corrects long‑term bias (motor mismatch, surface drift).
- **$K_d$** damps oscillations (prevents overshoot on corners).

In this repository, PID shows up in two ways:
1. **Encoder balancing** to keep the robot moving straight.
2. **Line‑following corrections** to keep the robot centered on the line.

## Hardware Assumptions
- Arduino Nano (ATmega328P)
- Dual DC motors with H‑bridge driver
- Quadrature encoders
- 3‑IR or 5‑IR reflectance sensor array

## Code Structure
### Main Program
- [src/main.cpp](src/main.cpp) — A simple 3‑sensor line‑following loop with motor drive helpers and encoder wiring. It focuses on straightforward, reliable behavior before adding PID complexity.

### Test & Experiments
The [test](test) folder contains experimental sketches and tuning runs. These are not PlatformIO unit tests—they are standalone sketches used during development.

- [test/five_ir_working.cpp](test/five_ir_working.cpp) — 5‑IR line follower logic with sharper turn handling.
- [test/five_ir_smoothing.cpp](test/five_ir_smoothing.cpp) — Adds speed smoothing to reduce jerk during fast direction changes.
- [test/five_ir_test.cpp](test/five_ir_test.cpp) — Another 5‑IR tuning variant, used to compare turn thresholds.
- [test/three_ir_working.cpp](test/three_ir_working.cpp) — Stable 3‑IR baseline logic for quick testing.
- [test/line_follow_overshoot_tuning.cpp](test/line_follow_overshoot_tuning.cpp) — Overshoot experiments with adjusted speeds and turn delays.
- [test/pid_straight_line.cpp](test/pid_straight_line.cpp) — PID with encoder feedback to keep motors matched when moving straight.
- [test/pid_library_balance.cpp](test/pid_library_balance.cpp) — Basic PID_v1 usage for encoder balancing.
- [test/pid_library_tuning.cpp](test/pid_library_tuning.cpp) — PID_v1 tuning run with higher gains and output analysis.
- [test/encoder_forward_test.cc](test/encoder_forward_test.cc) — Minimal motor/encoder wiring sanity check.
- [test/matlab_sim_data.txt](test/matlab_sim_data.txt) — Logged values for MATLAB simulation and PID validation.
- [test/encodertestcodes/encoder_interrupt_read.ino](test/encodertestcodes/encoder_interrupt_read.ino) — Encoder interrupt read example.
- [test/MotorTest/nano_benchmark.ino](test/MotorTest/nano_benchmark.ino) — Arduino Nano benchmark sketch (CPU timing reference).

## Tuning Notes
- Start with conservative $K_p$ values and increase until the robot begins to oscillate, then back off slightly.
- Add small $K_d$ to smooth sharp turns.
- Use $K_i$ sparingly to avoid slow drift or wind‑up.

## Build & Upload
This is a PlatformIO project. The active environment is defined in [platformio.ini](platformio.ini).

---
If you’re extending the logic, keep the `forward()` helper consistent across sketches so motor direction conventions stay aligned.
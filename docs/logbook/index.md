Logbook index

This folder contains logbook pages for key project files. Each page describes the file's purpose, main APIs/symbols, data shapes, a short recipe to recreate it, important notes, and a minimal list of edge cases.

Pages included:

- `src_main.cpp.md` — Project entry point: initialization and main control flow.
- `src_Display.hpp.md` — Display abstraction for LVGL/native display.
- `src_autonomous_PIDController.hpp.md` — PID controller header design and usage.
- `src_data_normal.c.md` — Small C utilities for normalization and clamping.
- `src_systems_Constants.hpp.md` — Project constants and configuration values.
- `src_systems_DriveTrain.hpp.md` — Drive subsystem: motor control and odometry helpers.
- `src_systems_Intake.hpp.md` — Intake control: rollers and deploy/stow.
- `src_systems_MatchLoad.hpp.md` — High-level loader state machine coordinating intake/indexer.
- `src_systems_MobileClamp.hpp.md` — Mobile clamp mechanism control and calibration.
- `src_systems_ColorSort.hpp.md` — Color sensor mapping and sorting actions (header).
- `src_systems_ColorSort_cpp.md` — Implementation notes for color sorting behavior and filtering.
- `src_systems_IMU_imu_wrapper.cpp.md` — IMU wrapper: calibration and heading helpers.
- `include_api.h.md` — Aggregate project API header guidance.
- `include_main.h.md` — Project-wide externs and forward declarations.

How to extend:
- To generate pages for more files, run this assistant with "create logbook pages for all files" or specify a directory (for example: `include/liblvgl`).
- I can also create a script to auto-generate skeleton pages for every file in the repo.

Generated: 2026-01-27

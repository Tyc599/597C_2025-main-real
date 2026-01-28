
# Methods Index

This single-file index summarizes all method-level documentation in `docs/logbook/methods/`. Click a link to open the full method page.

## Table of contents
- [IMU](#imu)
- [Main lifecycle](#main-lifecycle)
- [DriveTrain](#drivetrain)
- [Intake](#intake)
- [PIDController](#pidcontroller)
- [ColorSort](#colorsort)
- [Display](#display)
- [MatchLoad & MobileClamp](#matchload--mobileclamp)

---

## IMU
- [imu_init(sample_rate_hz=200, enable_dmp=false)](methods/imu_init.md) — Initialize IMU hardware. Inputs: sample_rate_hz, enable_dmp.
- [imu_calibrate(timeout_ms=2000, motion_threshold_deg_s=1.5) -> bool](methods/imu_calibrate.md) — Compute gyro/accel biases while stationary. Output: success.
- [imu_get_heading_deg() -> double](methods/imu_get_heading_deg.md) — Return bias-corrected heading in degrees.
- [imu_get_gyro_dps() -> Vec3](methods/imu_get_gyro_dps.md) — Return bias-corrected angular rates.
- [imu_reset_heading(new_heading_deg=0.0)](methods/imu_reset_heading.md) — Re-zero reported heading via offset.
- [imu_is_ready() -> bool](methods/imu_is_ready.md) — Whether IMU init/calibration completed.

## Main lifecycle
- [main.initHardware()](methods/main_initHardware.md) — Central hardware init routine.
- [main.runAutonomous()](methods/main_runAutonomous.md) — Run deterministic autonomous routine.
- [main.runOperatorControl()](methods/main_runOperatorControl.md) — Teleop loop mapping controller inputs to subsystems.

## DriveTrain
- [DriveTrain::init()](methods/DriveTrain_init.md) — Configure motors, encoders, odometry.
- [DriveTrain::setOpenLoop(left_percent, right_percent)](methods/DriveTrain_setOpenLoop.md) — Direct motor percent control.
- [DriveTrain::setVelocity(left_mps, right_mps)](methods/DriveTrain_setVelocity.md) — Closed-loop velocity commands in m/s.

## Intake
- [Intake::spinPercent(percent)](methods/Intake_spinPercent.md) — Spin intake rollers at percent power.
- [Intake::stop()](methods/Intake_stop.md) — Stop intake and clear state.

## PIDController
- [PIDController::update(dt, setpoint, measurement) -> double](methods/PIDController_update.md) — Compute PID output.

## ColorSort
- [ColorSort::detect() -> Color](methods/ColorSort_detect.md) — Detect color from sensor.
- [ColorSort::actuateFor(Color)](methods/ColorSort_actuateFor.md) — Actuate sorting mechanism for a color.

## Display
- [Display::showText(line, text)](methods/Display_showText.md) — Show a line of text on the display.

## MatchLoad & MobileClamp
- [MatchLoad::loadCycle()](methods/MatchLoad_loadCycle.md) — Single high-level load cycle state machine.
- [MobileClamp::setClamp(closed)](methods/MobileClamp_clamp.md) — Open/close clamp.

---

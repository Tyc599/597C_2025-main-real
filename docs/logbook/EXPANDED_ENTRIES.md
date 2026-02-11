# Expanded logbook entries (generated 2026-02-03)

This file collects expanded, actionable logging recommendations for the existing per-file logbook entries under `docs/logbook` and `docs/logbook/methods`.

Note: I updated all entries here except the ramp-related method `DriveTrain_moveHorizontal_ramp.md` as requested.

---

## How to use these entries

- Each section below maps to an existing `docs/logbook` file. Use the short checklist and suggested log lines to add runtime logs, or copy the suggestions into the corresponding `.md` file if you prefer per-file in-place edits.
- Suggested log formats include both a human-readable plain-text and an optional JSON-lines format for post-match analysis.

---

## Global logging recommendations (apply across the repo)

- Log format (plain): `[YYYY-MM-DD HH:MM:SS] [LEVEL] [module/file:line] message {k:v,...}`
- JSON-lines example: `{"ts":"2026-02-03T15:04:05Z","level":"INFO","module":"main","msg":"init_complete","imu_ready":true}`
- Minimum fields: timestamp, level, module, message. Add contextual keys (sensor_id, value, units, duration_ms).
- Levels: DEBUG / INFO / WARN / ERROR. Keep DEBUG disabled in contest builds unless explicitly enabled.
- Provide a small Logger utility (macro friendly) that injects file/line and supports compile-time disable.
- Consider a circular log file on persistent storage for post-match retrieval; otherwise ensure USB/serial logs are timestamped.

---

## Expanded entries per doc

### docs/logbook/src_main.cpp.md
- Purpose: project entry and startup sequence.
- Logs to add: `init_start`, `platform_init_done`, `sensors_calibrated`, `tasks_started`, `mode_selected`.
- Example: `[2026-02-03 15:04:05] INFO main: init_complete {imu_ready:true, battery_v:12.4}`
- TODO: Add startup trace in `main()` that records durations for each blocking init.

### docs/logbook/src_Display.hpp.md
- Purpose: Display helper APIs.
- Logs to add: `display_init`, `show_text` calls including message text and screen id, and display errors (framebuffer overflow, comms failure).
- Example: `[2026-02-03 15:06:00] DEBUG Display::showText: message="Boot OK"`.
- Suggestion: Keep display logs at DEBUG level to avoid clutter in match logs.

### docs/logbook/src_autonomous_PIDController.hpp.md
- Purpose: PID controller behavior and update usage.
- Logs to add: PID update events (input, setpoint, output, error) at DEBUG for tuning. WARN if integrator windup or saturation detected.
- JSON example: `{"ts":"...","level":"DEBUG","module":"PID","setpoint":1.0,"input":0.95,"output":0.12}`

### docs/logbook/src_data_normal.c.md
- Purpose: data processing routines.
- Logs: data load/start/complete, parsing errors, and sample rates. Include sample IDs where applicable.

### docs/logbook/src_systems_ColorSort.hpp.md & src_systems_ColorSort_cpp.md
- Purpose: sensor-driven color sorting.
- Logs: detection events, actuator commands (actuate start/stop), sensor confidence levels.
- Example: `[INFO] ColorSort: detected=RED confidence=0.92 action=actuate`.

### docs/logbook/src_systems_Constants.hpp.md
- Purpose: configuration constants.
- Logs: no runtime logs, but add metadata: source of truth, units, and recommended change procedures.

### docs/logbook/src_systems_DriveTrain.hpp.md
- Purpose: DriveTrain public API.
- Logs: high-level motion commands (setOpenLoop, setVelocity, driveDistance), command source (auton/operator), and start/end events with durations.
- Example: `INFO DriveTrain:setVelocity {target_mps:0.5, actual_mps:0.49}`

### docs/logbook/src_systems_IMU_imu_wrapper.cpp.md
- Purpose: IMU wrapper and calibration.
- Logs: calibration start/finish, health checks, gyro/accel read errors, and heading updates at INFO/DEBUG depending on frequency.
- Example: `INFO IMU:calibrate complete {duration_ms:2500}`

### docs/logbook/src_systems_Intake.hpp.md
- Purpose: Intake control.
- Logs: spin start/stop, requested percent, and motor faults.
- Example: `INFO Intake:spinPercent {percent:80, requested_by:operator}`

### docs/logbook/src_systems_MatchLoad.hpp.md
- Purpose: Match load cycle routines.
- Logs: load cycle start/complete, object acquired events, and retries.

### docs/logbook/src_systems_MobileClamp.hpp.md
- Purpose: MobileClamp actuator.
- Logs: clamp/unclamp events and sensor state at action time.

### docs/logbook/include_api.h.md & include_main.h.md
- Purpose: API and main header documentation.
- Logs: no runtime logs; add recommended instrumentation points and API usage examples.

### docs/logbook/index.md
- Purpose: table of contents.
- Action: add a short section describing the logging conventions used in the expanded entries, including the recommended log format and where to find persistent logs.

---

## Methods (docs/logbook/methods)
Below are per-method suggestions. Copy them into the corresponding method `.md` files if you want in-place updates.

- DriveTrain_init.md: log init start/complete, durations, encoder zero results.
- DriveTrain_setOpenLoop.md: log requested percent and actual voltage/current if available.
- DriveTrain_setVelocity.md: log setpoint, actual velocity, loop error, and corrective output at INFO; leave detailed samples to DEBUG.
- DriveTrain_moveHorizontal_ramp.md: (left unchanged per request)
- Display_showText.md: log text emissions at DEBUG level.
- ColorSort_actuateFor.md: log actuation start/stop and bounding durations.
- ColorSort_detect.md: log detections with bounding confidence.
- Intake_spinPercent.md / Intake_stop.md: log start/stop and percent.
- MatchLoad_loadCycle.md: log cycle start/complete and object detection events.
- MobileClamp_clamp.md: log clamp actions and limit switch states.
- PIDController_update.md: log input/setpoint/output at DEBUG for tuning; warn on unusual large errors.
- imu_*.md (init, calibrate, get_heading_deg, get_gyro_dps, is_ready, reset_heading): log calibration lifecycle, sensor reads, errors, and readiness transitions.
- main_initHardware.md, main_runAutonomous.md, main_runOperatorControl.md: add traces for mode entry/exit and key state changes.
- methods_index.md: add pointer entries to these expanded suggestions.

---

## Next steps I can take for you

- Option A (recommended): I can apply these expanded entries back into each individual `.md` file in `docs/logbook` and `docs/logbook/methods` (except `DriveTrain_moveHorizontal_ramp.md`) so each doc contains the corresponding expanded section. This is more work but keeps expanded notes next to the source file.

- Option B (current): Keep this aggregated `EXPANDED_ENTRIES.md` as the single place for all expansions (already created). This avoids modifying many files at once.

Tell me which option you prefer. If you want Option A, I'll proceed to update each doc in-place (I will update the todo list and make the edits). If you prefer Option B, we're done: the expanded log details are in `docs/logbook/EXPANDED_ENTRIES.md`.

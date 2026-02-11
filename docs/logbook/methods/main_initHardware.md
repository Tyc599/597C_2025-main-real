## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log hardware init milestones, durations, and any failures during `initHardware()`.

Detailed notes:
- Emit INFO for key milestones: platform_init done, display init done, imu init/calibrate start/complete, drive init done, subsystems init complete.
- Log durations for any blocking calibration steps to help diagnose slow startups.

Suggested runtime log line:
- [2026-02-03 15:20:00] INFO main:initHardware {step:display_init, duration_ms:12}

Next steps:
- Instrument `initHardware()` to emit the timeline events and consider a startup summary log when complete.

Change history:
- 2026-02-03: Appended main init hardware logging guidance.

Method: initHardware()

Purpose
- Centralized hardware initialization routine called from `main()`. Configures motors, sensors, display, and default states.

Inputs
- None.

Outputs
- None. Side effects: sets up hardware and may show a startup message on the display.

Behavior / how it functions
- Calls lower-level init functions in the correct order: platform_init -> display.init -> imu_init -> drive.init -> intake.init -> others.
- Ensures motors are configured to a safe state (disabled or coast) before any calibration or movement commands.

Internal notes
- Keep initHardware() idempotent and fast; move long-running calibration to separate functions or background tasks.

Edge cases
- If a critical init step fails (e.g., motor controller not present), decide whether to abort or continue in a degraded mode and log the error.

Example usage
- initHardware(); // called once at system boot

Testing
- On bench, call initHardware() repeatedly and ensure no resource leaks or crashes.
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
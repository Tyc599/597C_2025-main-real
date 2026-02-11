## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Teleop loop logging: mode entry/exit, controller connection events, and critical operator actions.

Detailed notes:
- Emit INFO when entering teleop and when controller connection state changes; log critical operator-triggered actions (e.g., intake on/off) with timestamps.
- Keep per-loop logs minimal; consider sampling important events only.

Suggested runtime log line:
- [2026-02-03 15:22:00] INFO Teleop: enter {controller_connected:true}

Next steps:
- Add event-based logging in `runOperatorControl()` and avoid per-loop noisy logs.

Change history:
- 2026-02-03: Appended operator control logging guidance.

Method: runOperatorControl()

Purpose
- Enter teleoperated control loop that reads controller inputs and commands subsystems accordingly.

Inputs
- None directly; reads controller state inside the loop.

Outputs
- None. Behavior: continuous loop until robot is disabled or match ends.

Behavior / how it functions
- Typical loop structure:
+ while(enabled) {
+   read controller inputs;
+   map inputs to drivetrain commands (e.g., tankDrive);
+   check buttons for mechanism triggers (intake, clamp);
+   sleep small delay (e.g., 10-20 ms);
+ }

Internal notes
- Keep loop latency low; avoid heavy operations.
- Debounce buttons and avoid issuing repeated start/stop commands unexpectedly.

Edge cases
- Lost controller connection: fall back to safe state (stop motors) and signal operator.

Example usage
- runOperatorControl();

Testing
- Ensure responsiveness and that no high-priority blocking operations occur in the loop.
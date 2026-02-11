## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Intake subsystem logging: spin actions, stops, jam events, and deploy/stow transitions.

Detailed notes:
- Log `spinPercent()` calls with percent and caller (operator/auton) at INFO.
- Emit WARN when jam detection triggers with current values and recovery actions.

Suggested runtime log line:
- [2026-02-03 15:10:30] INFO Intake: spinPercent {percent:80, caller:operator}

Next steps:
- Add intake logging to `intake.spinPercent()` and `intake.stop()` and document thresholds.

Change history:
- 2026-02-03: Appended Intake-specific logging guidance.

File: src/systems/Intake.hpp
Purpose: Controls the intake mechanism: rollers, actuators, sensors.

Overview:
- Basic methods: spin(rate), stop(), deploy(), stow().
- May include jam detection using current or encoder feedback.

Key API:
- class Intake { init(); spinPercent(percent); stop(); isDeployed(); }

Data shapes:
- State enum { STOWED, DEPLOYED, DEPLOYING }.

Recreation steps:
1. Create a class controlling the intake motor(s) and a solenoid for deployment.
2. Implement `spinPercent()` with safe limits and ramping if needed.
3. Add a simple jam-detect: if current > threshold for N ms, reverse briefly.

Notes:
- Keep actuator safety in mind: timeouts on deploy/stow.

Last-modified: 2026-01-27
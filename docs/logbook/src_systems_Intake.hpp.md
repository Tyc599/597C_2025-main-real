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
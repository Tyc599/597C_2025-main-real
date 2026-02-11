```markdown
## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Velocity command logging guidance: setpoint, actuals, and tuning diagnostics.

Detailed notes:
- Log setVelocity calls at INFO with requested m/s and caller (auton/operator).
- At DEBUG, log setpoint vs actual velocity and loop error for tuning.

Suggested runtime log line:
- [2026-02-03 15:14:00] INFO DriveTrain::setVelocity {left_mps:1.2,right_mps:1.2,caller:auton}

Next steps:
- Add optional sampled telemetry to capture actual velocities periodically under a DEBUG flag.

Change history:
- 2026-02-03: Appended velocity command logging guidance.

Method: DriveTrain::setVelocity(left_mps, right_mps)

Purpose
- Command the drivetrain with target velocities (meters per second) using internal velocity controllers.

Inputs
- double left_mps, double right_mps: target linear velocities for each side.

Outputs
- None. Side effects: closed-loop velocity control engages to reach requested speeds.

Behavior / how it functions
- Convert target velocity to motor RPM or encoder ticks/s using wheel circumference and gear ratios.
- Pass the converted target into per-motor PID controllers or platform velocity API.

Internal notes
- Ensure velocity feedforward and PID gains are tuned for responsiveness without overshoot.

Edge cases
- Large abrupt changes in target should be ramped to avoid mechanical stress.

Example usage
- drive.setVelocity(1.2, 1.2); // both sides 1.2 m/s

Testing
- Run step responses and log actual speed vs. commanded to tune controllers.
```
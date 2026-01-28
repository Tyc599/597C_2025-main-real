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
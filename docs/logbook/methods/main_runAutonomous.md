Method: runAutonomous()

Purpose
- Execute the autonomous routine(s) for the robot match phase. Typically a sequence of motion and mechanism commands executed without operator input.

Inputs
- None (but may read a selected routine index or parameters from configuration).

Outputs
- None. Side effects: moves the robot and actuates mechanisms.

Behavior / how it functions
- Uses DriveTrain and subsystems with blocking or non-blocking commands to accomplish tasks.
- Should be deterministic: no random delays or human input required.

Internal notes
- Keep routines small and testable. Prefer composing small reliable primitives: driveDistance(), turnAngle(), clamp.setClamp(true).

Edge cases
- Sensor failures: abort or fallback gracefully.
- Time limits: ensure routine completes before match phase ends or provide safe stop.

Example usage
- runAutonomous(); // called by main when autonomous mode selected

Testing
- Run the routine in a field-sim or on a bench and log expected positions vs. actual.
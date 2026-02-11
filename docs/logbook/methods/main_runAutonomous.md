## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log autonomous routine start/stop, chosen routine, and key milestones.

Detailed notes:
- Emit INFO at autonomous start with routine id/description, and at completion with duration and final state.
- Log critical failures or sensor timeouts with WARN/ERROR including context.

Suggested runtime log line:
- [2026-02-03 15:21:00] INFO Autonomous: run start {routine:default}

Next steps:
- Instrument `runAutonomous()` entry/exit and key high-level actions for post-match analysis.

Change history:
- 2026-02-03: Appended autonomous logging guidance.

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
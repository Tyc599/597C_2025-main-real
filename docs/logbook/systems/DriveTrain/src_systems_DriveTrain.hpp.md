```markdown
## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Add DriveTrain logging recommendations for commands, state changes, and safety events.

Detailed notes:
- Log high-level motion commands (driveDistance, setVelocity) at INFO with start time, parameters, and completion time/duration.
- Log safety events (wheel lock engaged, encoder errors) at WARN/ERROR.

Suggested runtime log line:
- [2026-02-03 15:10:00] INFO DriveTrain: driveDistance start target_m=1.0 source=auton

Next steps:
- Add `DriveTrain::logStatus()` to periodically emit odometry and velocity for telemetry, guarded by a DEBUG flag.

Change history:
- 2026-02-03: Appended expanded DriveTrain logging guidance.

File: src/systems/DriveTrain.hpp
Purpose: Interface for the robot drive subsystem: motor grouping, motion commands, odometry helpers.

Overview:
- Provides high-level methods: setVoltage(left, right), tankDrive(leftSpeed, rightSpeed), driveDistance(meters), turnAngle(deg).
- Manages motor objects, encoders, and optionally odometry state.

Key classes / API:
- class DriveTrain { init(); setOpenLoop(L,R); setVelocity(L,R); driveDistance(target); resetOdometry(); getPose(); }
- Uses PID controllers for closed-loop movement.

Data shapes:
- Pose struct { double x, y, heading }.
- Encoder readings (ints or doubles) converted to meters.

Recreation steps:
1. Define a DriveTrain class that owns motor controller objects and encoders.
2. Implement conversion helpers between encoder ticks and meters.
3. Provide simple blocking `driveDistance()` that uses a PID loop or a non-blocking command pattern.

Edge cases:
- Handle stalled motors, sensor timeouts, and small dt.

Last-modified: 2026-01-27
```
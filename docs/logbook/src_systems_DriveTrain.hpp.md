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
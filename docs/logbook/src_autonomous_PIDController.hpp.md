File: src/autonomous/PIDController.hpp
Purpose: Header-only or small header for a PID controller used by autonomous routines.

Overview:
- Provides a PIDController class with configurable gains, limits, and an update(dt, setpoint, measurement) method.

Key API:
- class PIDController { PIDController(kp, ki, kd); double update(double dt, double setpoint, double measurement); void reset(); }
- Parameters: kp, ki, kd, integral_limit, output_limit.

Data shapes:
- Internals: double last_error, integral_accum, last_output.

Recreation steps:
1. Define the class in a header with inline methods or a small cpp if preferred.
2. Implement anti-windup by clamping integral_accum.
3. Ensure `update()` returns the computed control effort and updates internal state.

Edge cases:
- dt==0 should be handled (return 0 or previous output).
- Large setpoint jumps: consider slew limiting.

Last-modified: 2026-01-27
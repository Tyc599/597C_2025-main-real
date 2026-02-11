## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: PID update logging for tuning; keep detailed logs at DEBUG.

Detailed notes:
- At DEBUG: log dt, setpoint, measurement, error, output, and integral state for tuning.
- Emit WARN if dt is zero or unusually large, or if integrator windup is detected.

Suggested runtime log line (DEBUG):
- {"ts":"2026-02-03T15:16:00Z","level":"DEBUG","module":"PID","dt":0.02,"setpoint":1.0,"measurement":0.95,"output":0.12}

Next steps:
- Add a toggle to enable sampled PID debug logs during bench tuning only.

Change history:
- 2026-02-03: Appended PID logging guidance.

Method: PIDController::update(dt, setpoint, measurement) -> double

Purpose
- Compute PID control output given the time delta, desired setpoint, and current measurement.

Inputs
- double dt: time in seconds since last update.
- double setpoint: desired target value.
- double measurement: current measured value.

Outputs
- double: control output (may be clamped to configured output limits).

Behavior / how it functions
1. error = setpoint - measurement
2. integral += error * dt; clamp integral to integral_limit
3. derivative = (error - last_error) / dt
4. output = kp*error + ki*integral + kd*derivative
5. clamp output to output_limit, possibly apply anti-windup if output saturated
6. last_error = error
7. return output

Internal notes
- Handle dt <= 0 by returning last_output or 0.
- Anti-windup: only accumulate integral when output is not saturated or when error drives integral towards unsaturation.

Edge cases
- Noisy measurements: consider using a derivative filter or smoothing on measurement.
- Large dt spikes: cap dt to a reasonable max to prevent huge integrator jumps.

Example usage
- double u = pid.update(0.02, 1.0, measured);

Testing
- Unit tests for step response, integral windup, and derivative handling are recommended.
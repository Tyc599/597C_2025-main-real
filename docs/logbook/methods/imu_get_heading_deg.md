Method: imu_get_heading_deg() -> double

Purpose
- Return the current vehicle heading (yaw) in degrees, bias-corrected and optionally smoothed.

Inputs
- None.

Outputs
- double: heading in degrees (commonly in either [-180,180) or [0,360) depending on project convention).

Behavior / how it functions
- The method reads fused orientation if the IMU provides it; otherwise it integrates bias-corrected gyro rates over time to derive heading.
- Applies an exponential moving average (alpha) if smoothing is configured.
- Applies stored offset so that calling `imu_reset_heading()` can re-zero the reported heading.

Internal notes
- Maintain `last_timestamp_ms` to compute dt for integration when needed.
- When integrating, convert gyro dps -> degrees by multiplying by dt (seconds).

Edge cases
- If IMU is not ready (calibration not done), return a fallback value (e.g., 0) or the last-known heading; document behavior.
- Handle wrap-around when adding small increments near ±180 degrees by normalizing.

Example usage
- heading = imu_get_heading_deg();

Testing
- Feed synthetic gyro data and assert integrated heading matches expectation.
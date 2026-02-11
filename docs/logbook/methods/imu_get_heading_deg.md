## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log heading reads at INFO with occasional DEBUG samples for tuning.

Detailed notes:
- Emit INFO-level heading updates at a low rate (e.g., 1 Hz) and DEBUG-level samples at higher rates for calibration runs.
- When `imu_is_ready()` is false, log a WARN when callers attempt to use heading values.

Suggested runtime log line:
- [2026-02-03 15:18:00] INFO IMU: heading {deg:12.4}

Next steps:
- Instrument `imu_get_heading_deg()` and ensure heading logs are rate-limited to avoid flooding serial output.

Change history:
- 2026-02-03: Appended heading read logging guidance.

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
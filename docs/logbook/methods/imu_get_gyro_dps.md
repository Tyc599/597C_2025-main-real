Method: imu_get_gyro_dps() -> Vec3

Purpose
- Return the current angular velocity (gyro) for X/Y/Z axes in degrees per second, bias-corrected.

Inputs
- None.

Outputs
- Vec3 { double x, y, z } in degrees per second.

Behavior / how it functions
- Reads raw gyro registers from the IMU, subtracts stored bias offsets, and returns the corrected values.
- Optionally applies a digital low-pass filter to reduce high-frequency noise.

Internal notes
- Keep returned values in the device's reference frame; provide helper to transform to vehicle coordinates if needed.

Edge cases
- If sensor read fails, return last-known good value or zero and set an error flag.

Example usage
- Vec3 g = imu_get_gyro_dps();

Testing
- Inject known gyro rates and confirm returned values are bias-corrected.

## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log gyro read errors and optionally sample gyro outputs for debug runs.

Detailed notes:
- On sensor read failures, emit ERROR and optionally return last-known valid value.
- Provide sampled DEBUG output during tuning: timestamped gyro dps for X/Y/Z.

Suggested runtime log line:
- [2026-02-03 15:17:30] DEBUG IMU: gyro {gx:0.01, gy:-0.02, gz:0.5}

Next steps:
- Instrument `imu_get_gyro_dps()` with optional DEBUG sampling controlled by a compile-time or runtime flag.

Change history:
- 2026-02-03: Appended gyro read logging guidance.

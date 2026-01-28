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
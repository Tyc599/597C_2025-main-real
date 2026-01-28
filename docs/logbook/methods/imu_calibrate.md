Method: imu_calibrate(timeout_ms = 2000, motion_threshold_deg_s = 1.5) -> bool

Purpose
- Compute and store static gyro/accelerometer bias offsets while the robot is stationary. Returns true if calibration completes successfully.

Inputs
- uint32_t timeout_ms: maximum time to attempt calibration.
- double motion_threshold_deg_s: maximum allowed angular rate during sampling; if exceeded, calibration fails.

Outputs
- bool: true on success (biases stored), false on failure (moved or timeout).

Behavior / how it functions
1. Start a sampling loop that reads raw gyro (dps) at a known sample interval.
2. For each sample, check if the magnitude of angular rate exceeds `motion_threshold_deg_s`. If so, abort and return false.
3. Accumulate samples and compute the mean bias per axis.
4. Store computed biases in persistent runtime state used by subsequent reads.
5. Mark IMU as ready and return true.

Internal notes
- Use a running average to avoid overflow for many samples.
- Sample count should be at least a minimal number (e.g., 50 samples) to reduce noise sensitivity.

Edge cases
- If device returns NaN or error reads, skip that sample but continue until timeout.
- If the robot cannot be held still, provide non-blocking alternative (background calibration) and expose partial biases.

Example usage
- if (!imu_calibrate(2000)) { display.showText("IMU CAL FAIL"); }

Testing
- Simulate small constant bias and assert the computed bias approximates the known value within tolerance.
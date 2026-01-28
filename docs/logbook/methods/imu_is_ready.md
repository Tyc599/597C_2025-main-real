Method: imu_is_ready() -> bool

Purpose
- Report whether the IMU wrapper has completed required initialization and calibration and is safe to use for control.

Inputs
- None.

Outputs
- bool: true if ready, false otherwise.

Behavior / how it functions
- Returns an internal flag set by `imu_init()`/`imu_calibrate()` when initialization and (optional) calibration succeed.
- Useful for gating control loops or for the UI to display calibration progress.

Edge cases
- If the IMU re-initializes or loses connection, ensure this flag is reset until a new calibration completes.

Example usage
- if (!imu_is_ready()) display.showText("IMU: not ready");

Testing
- Mock calibration success and failure and verify imu_is_ready() matches expected state.
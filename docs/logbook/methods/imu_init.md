## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log initialization parameters and success/failure of `imu_init()`.

Detailed notes:
- Emit INFO on init start with requested sample_rate and flags; emit INFO on successful init and WARN/ERROR if hardware not present.

Suggested runtime log line:
- [2026-02-03 15:18:30] INFO IMU:init {sample_rate_hz:200, enable_dmp:false}

Next steps:
- Add init logs and ensure idempotent calls are noted in logs to help debugging double-inits.

Change history:
- 2026-02-03: Appended IMU init logging guidance.

Method: imu_init(sample_rate_hz = 200, enable_dmp = false)

Purpose
- Initialize the IMU hardware and driver with the requested sample rate and features. Prepare internal state for subsequent reads.

Inputs
- int sample_rate_hz: desired sensor sampling rate in Hertz (default 200).
- bool enable_dmp: enable device motion processing (fusion) if available.

Outputs
- None (void). Side effects: configures hardware, allocates buffers, sets `imu_is_ready()` false until calibration completes.

Behavior / how it functions
- Configures the IMU driver registers or platform API to use `sample_rate_hz`.
- Sets up interrupts or polling timer for new-sample notification.
- Allocates or initializes data structures for biases, last timestamps, and filters.
- Optionally enables fused orientation (DMP) if supported by the sensor and `enable_dmp` is true.

Internal notes
- Ensure idempotent init: calling `imu_init()` twice should not double-allocate or leave the device in an inconsistent state.
- Defer heavy calibration to `imu_calibrate()` so `imu_init()` stays fast.

Edge cases
- Unsupported sample rates: clamp to nearest supported value and log a warning.
- Failure to initialize: return gracefully or set an error flag for higher-level code to handle.

Example usage
- imu_init(200, false);

Testing
- In bench tests, verify `read_raw_gyro()` returns sensible values (near zero when stationary) after init.
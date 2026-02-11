````markdown
## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: IMU wrapper logging recommendations: calibration lifecycle, readiness transitions, and sensor health.

Detailed notes:
- Emit logs for calibration start/complete and include duration_ms and success boolean.
- Log periodic heading updates at INFO (low rate) or DEBUG (high rate) with `heading_deg` and filter alpha used.
- On sensor errors or reconnects, emit ERROR-level logs with device id/details.

Suggested runtime log lines:
- [2026-02-03 15:09:00] INFO IMU: calibrate_start {timeout_ms:2000}
- [2026-02-03 15:09:02] INFO IMU: calibrate_complete {duration_ms:2034, success:true}
- {"ts":"2026-02-03T15:09:05Z","level":"INFO","module":"IMU","msg":"heading","heading_deg":12.4}

Next steps:
- Add `LOG_INFO` calls to `imu_init()`, `imu_calibrate()` and `imu_is_ready()` to emit lifecycle events.

Change history:
- 2026-02-03: Appended IMU-specific logging guidance and examples.

File: src/systems/IMU/imu_wrapper.cpp
Purpose: Thin wrapper around the IMU sensor that provides a stable, calibrated heading and convenient helper functions for the rest of the robot (drive control, odometry, autonomous actions).

Overview (detailed):
- Responsibilities:
	- Initialize IMU hardware with the correct settings (update rate, units, filters).
	- Run a calibration routine that measures and stores static offsets for gyro and accelerometer biases.
	- Provide time-stamped readings (heading, angular velocity, linear accel) and a simple API: getHeading(), getAngularVelocity(), resetHeading(), isReady().
	- Offer optional smoothing (low-pass filter) and wrapping to [-180,180) or [0,360).

Key functions & signatures (recommended):
- void imu_init(int sample_rate_hz = 200, bool enable_dmp = false):
	- Initialize the IMU peripheral with `sample_rate_hz` and optional fused sensor features.

- bool imu_calibrate(uint32_t timeout_ms = 2000, double motion_threshold_deg_s = 1.5):
	- Runs a blocking calibration that samples the gyro and accelerometer while the robot is stationary. Returns true if calibration completed successfully within timeout_ms. Stores per-axis bias offsets.

- double imu_get_heading_deg():
	- Returns the current fused yaw/heading in degrees. Uses stored offsets and applies smoothing if enabled.

- struct Vec3 { double x, y, z; };
- Vec3 imu_get_gyro_dps():
	- Returns raw or bias-corrected angular rate in degrees per second.

- void imu_reset_heading(double new_heading_deg = 0.0):
	- Resets internal heading offset so the next `imu_get_heading_deg()` returns `new_heading_deg`.

- bool imu_is_ready():
	- Returns true once initialization and (optional) calibration are done.

Internal representation & data shapes:
- Stored biases: struct Bias { double gx_off, gy_off, gz_off; double ax_off, ay_off, az_off; }.
- Pose-like state: { double heading_deg; double last_timestamp_ms; Vec3 last_gyro; }
- Filter parameters: alpha for exponential smoothing (0..1), sample interval dt in seconds.

Calibration algorithm (pseudocode):
1. Start a timer; collect N samples until timeout_ms.
2. For each sample, read raw gyro and accel values and accumulate sums.
3. Compute mean for each axis: bias = sum / count.
4. If any sample's magnitude (|gyro|) exceeds motion_threshold_deg_s during sampling, abort and return false.
5. Store biases and mark imu as ready.

Example implementation snippet (pseudocode):
```
bool imu_calibrate(timeout_ms, motion_threshold) {
	start = now_ms();
	count = 0;
	sum = {0,0,0};
	while (now_ms() - start < timeout_ms) {
		g = read_raw_gyro(); // dps
		if (norm(g) > motion_threshold) return false; // moved, abort
		sum += g;
		count++;
		sleep(sample_interval_ms);
	}
	bias = sum / count;
	store_bias(bias);
	ready = true;
	return true;
}
```

Smoothing & filtering:
- Use an exponential moving average on heading: heading = alpha * new_heading + (1-alpha) * heading.
- Recommended alpha ~ 0.15 for moderate smoothing without large lag. Make alpha configurable.

Heading wrapping and continuity:
- When integrating gyro into heading, take care to wrap into [-180,180) or [0,360) consistently. Provide helper functions: normalize_deg(d) and wrap_deg(d).
- When resetting heading, apply an offset rather than changing historical state so callers can re-zero without discontinuity in filters.

Example usage (how other subsystems use this wrapper):
- At startup: imu_init(); if (!imu_calibrate()) show calibration failed and retry or continue in degraded mode.
- Odometry: use imu_get_heading_deg() each control loop to fuse heading with encoder-based pose.

Tests & validation:
- Unit tests (if hardware simulation is available): feed synthetic gyro data and assert the integrated heading matches expected values.
- Integration: log raw vs. corrected gyro values during a test spin to verify bias subtraction.

Edge cases and failure modes:
- Long blocking calibration can delay startup—provide an asynchronous calibration option or `imu_is_ready()`.
- If the IMU resets or disconnects, detect via sensor error codes and reinitialize automatically.
- Handle large shocks: if accelerometer spikes are extreme, ignore single-sample outliers during calibration.

Performance notes:
- Keep sensor reads non-blocking in the main control loop; read at the configured `sample_rate_hz` in a dedicated task if using an RTOS.

Last-modified: 2026-01-27 (expanded with algorithms, APIs, and examples)
````

*** End Patch
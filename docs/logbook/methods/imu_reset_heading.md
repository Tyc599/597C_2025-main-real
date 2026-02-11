## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log heading resets including requested new heading and caller.

Detailed notes:
- Emit INFO on `imu_reset_heading()` calls with `new_heading_deg` and whether smoothing buffers were reset.

Suggested runtime log line:
- [2026-02-03 15:19:30] INFO IMU:reset_heading {new_deg:0.0, reset_filter:false}

Next steps:
- Instrument `imu_reset_heading()` and consider adding an option to force filter reset and log which mode was used.

Change history:
- 2026-02-03: Appended imu reset heading logging guidance.

Method: imu_reset_heading(new_heading_deg = 0.0)

Purpose
- Set the current reported heading to `new_heading_deg` by adjusting an internal offset. Does not retroactively change stored history.

Inputs
- double new_heading_deg: desired heading after reset.

Outputs
- None.

Behavior / how it functions
- Compute `offset = new_heading_deg - current_raw_heading` and store it. Future calls to `imu_get_heading_deg()` return `raw_heading + offset` (normalized).
- Keep filter state consistent: apply offset without resetting smoothing buffers to avoid large jumps, or optionally reset filter state if a clean jump is desired.

Internal notes
- Use offset rather than rewriting historical integrated value to keep implementation simple.

Edge cases
- If smoothing is enabled, a sudden heading reset may be smoothed out; provide a mode to reset smoothing buffers when re-zeroing.

Example usage
- imu_reset_heading(0.0); // make current heading read as 0°

Testing
- After reset, call imu_get_heading_deg() and assert it's within small epsilon of `new_heading_deg`.
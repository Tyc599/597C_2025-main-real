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
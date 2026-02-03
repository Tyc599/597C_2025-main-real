```markdown
Method: DriveTrain::moveHorizontal(inches, velocity) — ramp-on-high-velocity

Purpose
- Smoothly ramp motor velocity when commanding horizontal moves (strafe/sideways) at
  high open-loop speeds to avoid large instantaneous RPM jumps and mechanical stress.

Inputs
- double inches: relative distance to travel (inches). Positive -> one direction, negative -> opposite.
- int32_t velocity: requested motor velocity (RPM units used by the MotorGroup API).

Outputs
- None. Side effects: motors perform a relative move for the requested distance. During the
  motion the runtime commanded velocity will be ramped if above the configured threshold.

Behavior / how it functions
- If |velocity| <= 55: behavior unchanged — motors are commanded directly at the requested velocity.
- If |velocity| > 55: the controllers begin at a magnitude of 55 (preserving sign) and linearly
  ramp to the requested magnitude over approximately 500 ms using 20 ms update steps. The
  implementation uses MotorGroup::move_velocity(...) to update the commanded RPM during ramping.
- The method still uses MotorGroup::move_relative(...) to set the travel target in encoder ticks;
  the ramping only affects the runtime velocity commands so the distance semantics remain identical.

Why this was added
- Several callers previously requested high open-loop velocities which resulted in abrupt
  motor commands. Ramping reduces mechanical stress, current spikes, and improves predictability
  when starting a quick move.

Internal notes / implementation details
- Threshold: 55 RPM (hard-coded in the current change). This matches the user's specified cutoff.
- Ramp profile: linear from 55 -> requested |velocity| over 500 ms with 20 ms steps (25 steps).
- The sign (direction) of the requested velocity is preserved so negative velocities ramp from -55 to
  the requested negative magnitude.
- Ramping is applied in both `moveHorizontal(double, int32_t)` and `moveHorizontalIMU(double, int32_t)`.

Edge cases
- If the requested magnitude is only slightly above 55, the ramp will complete quickly (few steps).
- If the robot is prevented from moving (eg. a stall or safety lock), the motor controllers still
  receive ramped commands — caller code should use `setWheelLock(true)` to prevent moving when needed.
- If you need a different threshold or ramp duration, move the constants into `Constants.hpp` and
  tune them there.

Example usage
- dt.moveHorizontal(24.5, 70); // will ramp from 55 -> 70 over ~500ms
- dt.moveHorizontal(-5, 60);   // negative direction; will ramp from -55 -> -60

Verification
- Project was compiled after the change: build completed successfully (warnings only).
- Recommended runtime checks: observe motor current and encoder traces during a high-velocity move
  and compare before/after to confirm the ramp reduces current spikes and smooths acceleration.

Related files
- `src/systems/DriveTrain.hpp` — functions modified: `moveHorizontal(double, int32_t)`,
  `moveHorizontalIMU(double, int32_t)`.

```
Method: DriveTrain::setOpenLoop(left_percent, right_percent)

Purpose
- Directly command motor output as a percent (-100..100 or -1.0..1.0) without closed-loop control.

Inputs
- double left_percent, double right_percent: requested motor outputs.

Outputs
- None. Side effects: motors commanded immediately.

Behavior / how it functions
- Scale percent to motor API units and issue set commands to each motor/group.
- Optionally apply ramping to avoid current spikes.

Internal notes
- Use safety clamps to prevent commanding beyond allowed limits.

Edge cases
- If motors are disabled by a safety condition, ignore set commands and log state.

Example usage
- drive.setOpenLoop(0.5, 0.5); // 50% forward

Testing
- Verify motors respond linearly across the range and that clamping works.
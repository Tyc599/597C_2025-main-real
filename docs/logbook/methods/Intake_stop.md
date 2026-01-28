Method: Intake::stop()

Purpose
- Safely stop the intake motors and clear any short-term state (ramp state, jam timer).

Inputs
- None.

Outputs
- None.

Behavior / how it functions
- Command motors to 0 (or configured hold torque if required).
- Clear ramping/state machines so subsequent `spinPercent()` starts from a known baseline.

Edge cases
- If a jam recovery was in progress, abort recovery and leave the intake stopped.

Example usage
- intake.stop();

Testing
- Ensure motors stop rapidly and that subsequent spin commands work predictably.
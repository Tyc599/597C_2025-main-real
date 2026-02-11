## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log intake stop events and reset of internal state.

Detailed notes:
- Emit INFO on `stop()` with a short reason (operator/timeout/safety) and any cleared flags.

Suggested runtime log line:
- [2026-02-03 15:14:50] INFO Intake::stop {reason:operator}

Next steps:
- Instrument `stop()` and ensure ramp state is logged when reset.

Change history:
- 2026-02-03: Appended intake stop logging guidance.

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
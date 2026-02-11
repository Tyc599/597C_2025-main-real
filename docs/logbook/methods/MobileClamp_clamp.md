Method: MobileClamp::setClamp(closed)

Purpose
- Close or open the clamp used to grip game elements.

Inputs
- bool closed: true to close, false to open.

Outputs
- None. Side effects: actuate solenoid/motor and update internal state.

Behavior / how it functions
- If controlled by a solenoid: set solenoid state accordingly.
- If motor-driven: move to a position using a simple profile or until a limit switch triggers.

Internal notes
- Debounce limit switches; use timeouts for motor-driven actions.

Edge cases
- If limit switches report inconsistent state, fallback to timed move and small hold torque.

Example usage
- mobileClamp.setClamp(true); // close

Testing
- Verify clamp responds and limit switches show expected states.
```

## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log clamp actions, limit switch states, and calibration runs.

Detailed notes:
- Emit INFO for `setClamp()` calls, include requested state and snapshot of limit switches.
- Emit WARN when limit switches are inconsistent or timeouts occur during motor-driven moves.

Suggested runtime log line:
- [2026-02-03 15:15:40] INFO MobileClamp:setClamp {closed:true, limit_switch:true}

Next steps:
- Add clamp logs and calibrate routine logs; debounce and log transitions cleanly.

Change history:
- 2026-02-03: Appended MobileClamp logging guidance.

```markdown
## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Initialize DriveTrain subsystem; configure motors, encoders, and default control modes.

Detailed notes:
- Log events: start init, motor config complete, encoder zeroed, init duration (ms), and any errors encountered.
- If encoder failures occur, emit an ERROR-level log with sensor id and fallback action.

Suggested runtime log line:
- [2026-02-03 15:05:10] INFO DriveTrain::init: completed {encoders_zeroed:true, duration_ms:42}

Next steps:
- Consider adding a `DRIVETRAIN_LOG()` macro that includes file/line and is disabled in release builds.

Change history:
- 2026-02-03: Appended expanded logbook entry and runtime logging suggestions.

Method: DriveTrain::init()

Purpose
- Initialize the DriveTrain subsystem: configure motor groups, encoders, and default control modes.

Inputs
- None.

Outputs
- None. Side effects: motors configured, internal pose reset.

Behavior / how it functions
- Initialize motor controller objects and configure inversion and gear ratios.
- Configure encoder interfaces (attach callbacks or set reading mode).
- Reset odometry and zero encoder counts.

Internal notes
- Ensure consistent units: choose meters or inches for distance conversions and document them.

Edge cases
- Encoder missing or returning noisy data: set an error bit and optionally disable closed-loop commands.

Example usage
- drive.init();

Testing
- Verify encoders read zero after reset and that motors accept open-loop commands.
```
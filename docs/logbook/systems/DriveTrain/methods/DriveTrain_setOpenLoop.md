```markdown
## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log requested open-loop commands, safety clamping, and any ignored commands due to safety.

Detailed notes:
- Emit INFO when an operator/auton requests open-loop commands with percent values and caller.
- If a command is ignored due to safety lock, emit WARN with reason.

Suggested runtime log line:
- [2026-02-03 15:13:30] INFO DriveTrain::setOpenLoop {left:0.5,right:0.5,caller:operator}

Next steps:
- Instrument `setOpenLoop()` and add a safety check log path.

Change history:
- 2026-02-03: Appended open-loop logging guidance.

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
```
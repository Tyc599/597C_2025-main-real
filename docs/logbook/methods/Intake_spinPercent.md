## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Instrument intake spin commands and jam detection events for troubleshooting.

Detailed notes:
- Emit INFO when `spinPercent()` is called with the percent and caller; emit WARN when jam detection triggers with current and duration.

Suggested runtime log line:
- [2026-02-03 15:14:30] INFO Intake::spinPercent {percent:80, caller:operator}

Next steps:
- Add logs to spinPercent and to any jam-recovery handlers.

Change history:
- 2026-02-03: Appended intake spin logging guidance.

Method: Intake::spinPercent(percent)

Purpose
- Spin the intake rollers at a specified percentage of maximum power to intake or expel game pieces.

Inputs
- double percent: -100..100 or -1.0..1.0 where sign indicates direction.

Outputs
- None. Side effects: motor outputs change accordingly.

Behavior / how it functions
- Scale `percent` to the motor controller API and command the motor(s).
- Optionally implement current-based jam detection: if current > threshold for N ms, reverse briefly.

Internal notes
- Implement soft-start ramp to prevent sudden current spikes.

Edge cases
- Jam detection may produce false positives on bench without load; make thresholds configurable.

Example usage
- intake.spinPercent(0.8); // 80% forward

Testing
- Verify spin direction and that jam detection triggers in controlled overloads.
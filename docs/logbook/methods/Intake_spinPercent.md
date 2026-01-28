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
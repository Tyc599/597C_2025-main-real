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
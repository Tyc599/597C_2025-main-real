File: src/systems/Constants.hpp
Purpose: Single location for project constants and configuration macros.

Overview:
- Defines constants like wheel diameter, gear ratios, PID defaults, motor ports, sensor ports.
- Used by subsystems to avoid magic numbers.

Key contents:
- constexpr ints for motor port numbers.
- constexpr doubles for physical dimensions and PID default gains.

Recreation steps:
1. Create a header with guarded defines or `inline constexpr` variables.
2. Group values by subsystem (DriveTrain, Intake, Sensors).
3. Document units for each constant.

Notes:
- Avoid hard-coded hardware magic in code; keep here.
- Consider enabling overrides via a `config.h` or build flags.

Last-modified: 2026-01-27
## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Document constants with units and recommend logging points for configuration changes.

Detailed notes:
- For any runtime-configurable constants, log the chosen configuration at startup (config source, overridden values).
- Document units next to each constant to prevent ambiguity in logs.

Suggested runtime log line:
- [2026-02-03 15:09:30] INFO Constants: wheel_diameter_m=0.075 gear_ratio=10.0

Next steps:
- Consider a `config_dump()` routine that logs all runtime constants at startup for easier debugging.

Change history:
- 2026-02-03: Appended expanded constants & logging guidance.

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
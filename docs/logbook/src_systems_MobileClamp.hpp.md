## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: MobileClamp logging: clamp/unclamp events, limit switch states, and calibration.

Detailed notes:
- Log `setClamp()` calls with requested state and sensor snapshot at INFO.
- Log calibration runs with duration and success/failure.

Suggested runtime log line:
- [2026-02-03 15:11:30] INFO MobileClamp: setClamp {closed:true, limit_switch:true}

Next steps:
- Add clamp logs to `setClamp()` and calibrate routines; consider WARN for inconsistent limit readings.

Change history:
- 2026-02-03: Appended MobileClamp logging guidance.

File: src/systems/MobileClamp.hpp
Purpose: Controls a mobile clamp mechanism for manipulating field elements.

Overview:
- Methods: clamp(), release(), liftTo(pos), calibrate().
- Integrates motor(s), limit switches, and possibly pneumatic actuators.

Key API:
- class MobileClamp { init(); setClamp(bool closed); moveTo(position); isAtPosition(); }

Recreation steps:
1. Provide motor control with position feedback or timed moves.
2. Use limit switches to calibrate zero position at startup.

Edge cases:
- Debounce limit switches; handle lost encoder scenarios by falling back to timed moves.

Last-modified: 2026-01-27
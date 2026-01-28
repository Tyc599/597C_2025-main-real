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
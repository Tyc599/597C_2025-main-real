File: src/systems/Color Sort/ColorSort.cpp
Purpose: Implementation for the color sorting subsystem.

Overview:
- Reads sensor, applies filtering or averaging, maps to a color enum, and commands actuators.

Key functions:
- ColorSort::detect() - returns Color after filtering samples.
- ColorSort::actuateFor(Color c) - performs the mechanical sequence.

Recreation steps:
1. Implement a circular buffer to average the last N color samples.
2. Map averaged RGB/HSV to thresholds configured in `Constants.hpp`.
3. Sequence actuator with safety checks (timeouts and sensor re-check).

Notes:
- Keep detection non-blocking if used inside fast loops.

Last-modified: 2026-01-27
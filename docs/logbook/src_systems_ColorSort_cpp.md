## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Implementation-level guidance for adding logs that record detections and actuation timelines.

Detailed notes:
- Log averaged sensor values and chosen thresholds at DEBUG for tuning.
- Emit INFO when an actuation sequence starts and ends with timestamps and result (success/failure).

Suggested runtime log line:
- [2026-02-03 15:09:05] INFO ColorSort::actuateFor: start color=RED duration_ms=150

Next steps:
- Add sampled detection logs during a nearby run for classifier tuning; keep detailed logs at DEBUG.

Change history:
- 2026-02-03: Appended expanded implementation-level ColorSort logging guidance.

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
## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Add recommended logging points for color detection and actuation.

Detailed notes:
- Log detection events with confidence at INFO (or DEBUG if frequent): detected=RED confidence=0.92
- Log actuator commands and durations at INFO so match logs show when items were routed.

Suggested runtime log line:
- [2026-02-03 15:09:00] INFO ColorSort: detected=RED confidence=0.92 action=actuate

Next steps:
- Document detection frequency and recommend sampling/aggregation to avoid log spam.

Change history:
- 2026-02-03: Appended expanded ColorSort logging guidance.

File: src/systems/ColorSort.hpp
Purpose: Header for the color sorting subsystem (detects color and actuates mechanisms to sort pieces).

Overview:
- Exposes methods: analyzeColor(sensorReading), sortAction(color), calibrateSensor().
- Interfaces with color sensor and actuator to route items.

Key API:
- enum Color { RED, BLUE, UNKNOWN };
- class ColorSort { init(); Color detect(); void actuateFor(Color); }

Data shapes:
- Color sensor raw structure (RGB/HSV ints or floats), thresholds table.

Recreation steps:
1. Wrap sensor reads into a `detect()` function that maps raw values to Color using thresholds.
2. Implement actuator sequence for sorting (timed motor move or solenoid toggle).

Notes:
- Provide a calibration routine to set thresholds using sample reads.

Last-modified: 2026-01-27
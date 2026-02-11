Method: ColorSort::detect() -> Color

Purpose
- Read the color sensor, apply filtering and thresholding, and return a `Color` enum (RED, BLUE, UNKNOWN).

Inputs
- None (reads sensor internally).

Outputs
- enum Color: { RED, BLUE, UNKNOWN }

Behavior / how it functions
- Read raw sensor values (RGB or HSV).
- Optionally average over last N samples to reduce noise.
- Map averaged values to color using predefined thresholds or a small classifier.

Internal notes
- Provide a calibration routine that captures sample readings for known colors and sets threshold boundaries.
- For HSV mapping, hue is often the most robust; for RGB, use ratios (R/(R+G+B)).

Edge cases
- Low lighting: sensor readings can be inconsistent — return UNKNOWN.
- Transitional values: use hysteresis to avoid flicker between RED/BLUE.

Example usage
- Color c = colorSort.detect();

Testing
- Use sample logs to verify detect() returns expected class for known inputs.
```

## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log detection events and confidence to help tune thresholds and classifiers.

Detailed notes:
- Emit INFO or DEBUG for detection events: include raw averaged sensor values and computed confidence.
- For low confidence or UNKNOWN results, emit DEBUG and consider a sampled summary to avoid spam.

Suggested runtime log line:
- [2026-02-03 15:12:30] INFO ColorSort::detect {detected:RED, confidence:0.92}

Next steps:
- Instrument `detect()` during a calibration run to capture representative samples for threshold tuning.

Change history:
- 2026-02-03: Appended detection logging guidance.

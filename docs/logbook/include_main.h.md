## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Documentation for `include/main.h` should note recommended instrumentation points and extern usage for logging.

Detailed notes:
- Document which global subsystem instances should be logged at startup (e.g., display, drive, imu).
- Recommend including `include/api.h` to bring LOG macros into translation units that include `main.h`.

Suggested runtime log line:
- [2026-02-03 15:07:10] INFO include/main.h: extern Display display; // declared

Next steps:
- Add a short section listing instrumentation points and macros to use for boot-time logs.

Change history:
- 2026-02-03: Appended expanded logbook entry for header-level logging guidance.

File: include/main.h
Purpose: Project-global declarations used across translation units (application entry prototypes, shared externs).

Overview:
- May declare `extern` references to global objects (e.g., Display display; DriveTrain drive;), and shared functions.

Key contents:
- include guards, forward declarations, externs for subsystems, and common helper prototypes.

Recreation steps:
1. Add include guards and forward declarations for core subsystem classes.
2. Declare `extern` instances that are defined in `main.cpp` or a single source file.

Notes:
- Prefer passing references instead of externs where possible; use externs sparingly.

Last-modified: 2026-01-27
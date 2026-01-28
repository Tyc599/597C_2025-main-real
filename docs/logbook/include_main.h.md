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
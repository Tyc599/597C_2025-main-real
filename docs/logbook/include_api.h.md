File: include/api.h
Purpose: Project-level API header that aggregates common includes, macros, and small utilities used by the project.

Overview:
- Typically includes platform headers, project `main.h`, and common macros like LOG(), ASSERT().

Key contents:
- include guards, macro helpers, and common typedefs.

Recreation steps:
1. Create `api.h` with include guards and include `pros/*` or platform headers.
2. Add logging macros that compile away in release builds.

Notes:
- Keep this header minimal to avoid heavy compile times.

Last-modified: 2026-01-27
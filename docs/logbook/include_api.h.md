## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Add logging macro recommendations for `include/api.h` and guidance for using them across the codebase.

Detailed notes:
- Define LOG macros here (LOG_INFO/LOG_WARN/LOG_ERROR/LOG_DEBUG) that include timestamp, level, file, and line.
- Provide a compile-time switch to disable DEBUG logs in contest builds (`#ifdef LOG_DEBUG_ENABLED`).

Suggested runtime log line:
- [2026-02-03 15:07:00] INFO include/api.h: LOG_INFO("system init complete")

Next steps:
- Implement macros in `include/api.h` and update other headers to include this file.

Change history:
- 2026-02-03: Appended expanded logbook entry with macro suggestions.

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
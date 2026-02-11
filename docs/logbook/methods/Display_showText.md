Method: Display::showText(line, text)

Purpose
- Render a short line of text to the display (status or debug message).

Inputs
- int line: row index on the screen (0..N-1).
- string text: text to display; truncated to the display width.

Outputs
- None. Side effects: updates graphical objects or framebuffer.

Behavior / how it functions
- Update an LVGL label or platform text object for the given line.
- If called from multiple tasks, use a mutex or dispatch updates to the display task.

Internal notes
- Avoid expensive string operations in the display task; prepare strings in caller and only pass final text.

Edge cases
- If LVGL not initialized, buffer messages and flush when ready.

Example usage
- display.showText(0, "Ready");

Testing
- Verify that text appears at correct lines and handles long strings gracefully.
```

## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Keep display logs at DEBUG and document what should be logged when showing text.

Detailed notes:
- Log `showText()` calls at DEBUG with line and a truncated text preview. Avoid logging user-sensitive data.

Suggested runtime log line:
- [2026-02-03 15:13:00] DEBUG Display::showText line=0 text="Ready"

Next steps:
- Update display wrapper to include optional `log_text` flag for debug builds.

Change history:
- 2026-02-03: Appended display logging guidance.

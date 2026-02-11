## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Add logging guidance for display operations; keep most display logs at DEBUG level.

Detailed notes:
- Log `display.init()` success/failure and `showText()` calls (include the text or a truncated preview) at DEBUG.
- Avoid heavy logging from high-frequency UI updates; aggregate or sample logs instead.

Suggested runtime log line:
- [2026-02-03 15:06:00] DEBUG Display::showText: line=0 text="Boot OK"

Next steps:
- Add examples of safe display logging and note which calls should be DEBUG vs INFO.

Change history:
- 2026-02-03: Appended expanded display logging guidance.

File: src/Display.hpp
Purpose: Abstraction for on-robot display. Provides simple APIs for drawing text, status bars, and basic widgets.

Overview:
- Lightweight wrapper over LVGL or platform display APIs.
- Offers methods: showText(), showStatus(), drawIcon(), clear().

Key classes / functions:
- class Display { init(), showText(line, text), showStatus(key, value), clear() }.
- Optional callback hooks for touch/inputs.

Data shapes:
- Small internal buffer for lines of text (string[]), display dimensions constants.

Recreation steps:
1. Include LVGL or native display headers.
2. Create `Display` class with an `init()` that creates LVGL objects.
3. Implement `showText(line, text)` to update a label object or framebuffer.
4. Provide `clear()` to reset the screen.

Notes:
- Keep update rate low to avoid blocking main loop.
- Consider thread-safety if display is updated from tasks.

Last-modified: 2026-01-27
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
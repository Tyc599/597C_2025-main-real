File: src/data/normal.c
Purpose: Data file containing normalization or lookup functions used by sensors or algorithms.

Overview:
- Small C file with utility functions (e.g., normalize sensor values, lookup tables for calibration).

Key functions to reproduce:
- float normalize_value(float raw, float in_min, float in_max, float out_min, float out_max);
- int clamp_int(int v, int lo, int hi);

Data shapes:
- Uses primitive numeric types and possibly static lookup arrays.

Recreation steps:
1. Create `normal.c` with a small set of pure functions and corresponding `normal.h` for declarations.
2. Implement straightforward arithmetic and bounds checks.
3. Add unit-style comments and example inputs.

Notes:
- Keep it side-effect free to be reusable.
- Add small tests if possible.

Last-modified: 2026-01-27
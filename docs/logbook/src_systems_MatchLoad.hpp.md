File: src/systems/MatchLoad.hpp
Purpose: Manages the mechanism used to load game elements during match play.

Overview:
- Coordinates intake, indexer, and feeder elements to reliably load and deliver game pieces.

Key API:
- class MatchLoad { init(); loadCycle(); feedToIndexer(); abort(); }

Data shapes:
- Simple state machine: IDLE -> INTAKING -> INDEXING -> COMPLETE.

Recreation steps:
1. Implement a small state machine coordinating subsystems (call into Intake and other classes).
2. Provide timing and sensor checks to progress states (e.g., ball present sensor).

Notes:
- Make transitions deterministic to avoid jams.

Last-modified: 2026-01-27
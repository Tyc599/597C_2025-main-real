## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: MatchLoad logging: state transitions, cycle start/complete, and sensor confirmations.

Detailed notes:
- Emit INFO for `loadCycle()` start and completion with durations and final state.
- Log sensor events that trigger state transitions (e.g., piece detected) at DEBUG/INFO.

Suggested runtime log line:
- [2026-02-03 15:11:00] INFO MatchLoad: loadCycle start {caller:auton}

Next steps:
- Instrument `loadCycle()` to emit these events and include timeout reasons when aborting.

Change history:
- 2026-02-03: Appended MatchLoad logging guidance.

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
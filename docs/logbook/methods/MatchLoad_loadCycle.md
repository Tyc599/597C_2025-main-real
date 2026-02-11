Method: MatchLoad::loadCycle()

Purpose
- Execute a single load cycle that acquires a game piece and prepares it for scoring or storage.

Inputs
- None.

Outputs
- None. Side effects: coordinates Intake, Indexer, and possibly ColorSort.

Behavior / how it functions
- State machine steps: IDLE -> INTAKING -> INDEXING -> COMPLETE.
- Each step waits for sensor confirmation (e.g., piece present) or a timeout before advancing.

Internal notes
- Use timeouts to avoid getting stuck if sensors fail.
- Expose progress state for UI/telemetry.

Edge cases
- If intake jams, abort and signal operator.

Example usage
- matchLoad.loadCycle();

Testing
- Simulate piece present sensors to validate transitions.
```

## Expanded logbook entry — 2026-02-03
- Author: (add author)
- Summary: Log load cycle start/complete, sensor triggers, and abort reasons.

Detailed notes:
- Emit INFO at cycle start and completion with durations and result.
- Emit WARN when timeouts or jams occur with context.

Suggested runtime log line:
- [2026-02-03 15:15:10] INFO MatchLoad: loadCycle start {mode:auton}

Next steps:
- Instrument the state transitions and timeout branches to make post-match debugging easier.

Change history:
- 2026-02-03: Appended MatchLoad logging guidance.

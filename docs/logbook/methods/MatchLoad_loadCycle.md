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
Method: ColorSort::actuateFor(Color c)

Purpose
- Execute the mechanical sequence to route a detected color to the correct bin/area.

Inputs
- Color c: the detected color to sort.

Outputs
- None. Side effects: actuators (motors/servos/solenoids) are toggled to perform sorting.

Behavior / how it functions
- For each color, perform a short timed sequence: e.g., rotate flipper to position A for RED, position B for BLUE, and return to neutral.
- Use sensor feedback if available to ensure successful actuation.

Internal notes
- Use non-blocking actuation if possible: start a timed state machine rather than blocking the main loop.
- Provide a method to force-stop the actuator in case of emergency.

Edge cases
- Actuator jam or failure: detect via current spike or lack of motion and abort.

Example usage
- colorSort.actuateFor(Color::RED);

Testing
- Verify actuation sequence and timing with a bench test and confirm items are correctly routed.
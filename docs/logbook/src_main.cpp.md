File: src/main.cpp
Purpose: Project entry point. Performs deterministic initialization of hardware and subsystems, starts background tasks (sensors, control loops), and switches into the match mode (autonomous, driver control) based on configuration or controller input.

Overview (detailed):
- Responsibilities:
	- Run minimal, deterministic platform initialization.
	- Initialize and calibrate subsystems (DriveTrain, IMU, Intake, Display) in a safe order.
	- Create background tasks: sensor polling, control loops, and telemetry logging.
	- Provide clear, documented handoff into `autonomous()` or `operatorControl()`.

Recommended initialization order and rationale:
1. Low-level platform/OS initialization
	 - Bring up the RTOS or set thread priorities if required.
	 - Initialize logging and debug serial so further init messages are visible.

2. Power and safety checks
	 - Verify battery voltage (if available) and delay start or signal error if below safe threshold.

3. Sensors and timing
	 - Initialize system tick/timers used by other subsystems.
	 - Initialize IMU hardware (but defer long calibration until motors are disabled).

4. Actuators (motors, pneumatics)
	 - Initialize motor controllers and set them to a safe disabled/neutral state.
	 - Configure brake/coast modes and current limits where supported.

5. Subsystems and high-level modules
	 - Initialize DriveTrain (configure encoders), Intake, MobileClamp, ColorSort.
	 - Initialize Display and UI elements.

6. Calibration & checks (blocking or asynchronous)
	 - IMU calibration: either block here until success or run async and rely on `imu_is_ready()` in callers.
	 - Zero encoders and calibrate limits using limit switches.

7. Start background tasks
	 - Sensor polling task (e.g., publish imu, sensors at sample rate).
	 - Control loop task(s) for closed-loop motion (50-200Hz depending on the controller).

8. Enter main operational mode
	 - Either: call `autonomous()` for competition autonomous run.
	 - Or: start `operatorControl()` loop which reads controller input and drives subsystems.

Example `main()` pseudocode (single-threaded RTOS-less variant):
```
int main() {
	platform_init();          // logging, sys tick
	power_check();            // battery safe?

	display.init();
	imu_init();
	drive.init();
	intake.init();
	colorSort.init();

	// Calibrate sensors but keep motors disabled during calibration
	if (!imu_calibrate(2000)) {
		display.showText("IMU CAL FAIL");
		// optionally retry or continue in degraded mode
	}

	encoder_zero_all();

	// start periodic tasks (example uses a simple thread API)
	start_task(sensor_task, priority_medium);
	start_task(control_task, priority_high);

	// Choose mode (from build-time flag, controller input, or stored config)
	if (auton_selected()) {
		runAutonomous();
	} else {
		runOperatorControl();
	}

	// keep main alive if tasks run separately
	while (true) sleep_ms(1000);
}
```

RTOS vs bare-metal notes:
- If using an RTOS (recommended for complex robots), create dedicated tasks for:
	- IMU & sensors polling (sample-rate timing).
	- A deterministic motion control loop (e.g., 50-200 Hz) for PID updates.
	- Telemetry/USB logging at a lower priority.
- Avoid doing heavy work in `main()`; use `main()` to set up and then return to the scheduler or block on a safe loop.

Thread-safety and shared state:
- Protect shared objects (DriveTrain state, sensors) with mutexes or by confining write access to a single owner task.
- Prefer message-passing (queues) for commands between tasks to avoid priority inversion and reduce locking complexity.

Example `initHardware()` responsibilities (compact):
- Configure motor ports and default control modes (coast/brake).
- Configure encoder polarity and zero position.
- Configure sensor sample rates (IMU, analog sensors).
- Initialize the display and show a startup banner.

Common pitfalls and how to avoid them:
- Calibrating IMU with motors enabled -> motors should remain disabled until calibration completes.
- Blocking long functions in interrupts or high-priority tasks -> move heavy work to background tasks.
- Starting control loops before sensors are ready -> ensure `sensor_task` or `imu_is_ready()` gates controllers.
- Unchecked hardware errors (encoder disconnects) -> add watchdogs and safe fallback behaviours.

Minimal examples for `runAutonomous()` and `runOperatorControl()` (pseudocode):
```
void runAutonomous() {
	// Example sequence: drive forward 1m, open clamp, back off
	drive.driveDistance(1.0); // blocking call that uses PID to reach distance
	clamp.setClamp(true);
	drive.driveDistance(-0.25);
}

void runOperatorControl() {
	while (true) {
		auto stick = controller.read();
		drive.tankDrive(stick.left, stick.right);
		if (controller.buttonPressed(B1)) intake.spinPercent(80);
		sleep_ms(10);
	}
}
```

Testing & validation strategy:
- Unit-testable pieces: PID controller, encoder-to-distance conversions, utility math.
- Integration tests: run the full init sequence on a bench setup, record telemetry and ensure each step completes within a reasonable time budget.

Last-modified: 2026-01-27 (expanded with init order, pseudocode, and pitfalls)

Recreate complexity: medium (requires coordination of hardware init, tasks, and calibration).
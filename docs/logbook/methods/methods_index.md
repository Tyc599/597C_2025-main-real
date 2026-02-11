
# Methods Index

This single-file index summarizes all method-level documentation in `docs/logbook/methods/`. Click a link to open the full method page.

## Table of contents


## IMU

## Main lifecycle

## DriveTrain

## Intake

## PIDController

## ColorSort

## Display

## MatchLoad & MobileClamp


## Expanded logging guidance summary (2026-02-03)
- A set of conventions and per-method recommendations have been appended to individual method pages. Key points:
	- Use timestamped logs with levels (DEBUG/INFO/WARN/ERROR).
	- Keep high-frequency sensor logs at DEBUG and provide sampled or aggregated telemetry for match runs.
	- Instrument lifecycle events (init/calibrate/start/stop) at INFO and errors at WARN/ERROR.

See each method page for detailed per-method logging suggestions.
- [DriveTrain::setOpenLoop(left_percent, right_percent)](methods/DriveTrain_setOpenLoop.md) — Direct motor percent control.

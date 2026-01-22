#pragma once

#include "../systems/Constants.hpp"

#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "../autonomous/PIDController.hpp"
#include <functional>

using namespace Constants;
using namespace pros;

// IMU heading accessor (defined elsewhere, e.g. in main).
// Declaration here so DriveTrain can call it.
extern double imu_get_heading(uint8_t);
// IMU forward-acceleration accessor (m/s^2). Implemented in imu_wrapper.cpp.
extern double imu_get_accel_x(uint8_t);

// Use `IMU_PORT` macro if defined at compile time; otherwise fall back to 10.
#ifndef IMU_PORT
static constexpr uint8_t DRIVE_IMU_PORT = 10;
#else
static constexpr uint8_t DRIVE_IMU_PORT = IMU_PORT;
#endif

class DriveTrain {
    Motor fl_mtr = Motor(fl_p);
    Motor btl_mtr = Motor(ml_p);
    Motor bl_mtr = Motor(bl_p);
    Motor fr_mtr = Motor(fr_p);
    Motor btr_mtr = Motor(mr_p);
    Motor br_mtr = Motor(br_p);

    MotorGroup left_g  = MotorGroup({-fl_p, ml_p, -bl_p});
    MotorGroup right_g = MotorGroup({fr_p, -mr_p, br_p});

    PIDController pidController = PIDController(kP, kI, kD, integral_threshold); 


    std::function<void(void)> teleMove;
    double average_vector(std::vector<double> input){
        double output = 0;
        for(int i = 0; i < input.size(); i++){
            output += input[i];
        }
        output /= input.size();
        return output;
    }
    public:

    DriveTrain() {
        left_g.tare_position();
        right_g.tare_position();
    }

    inline void tankDrive(signed char leftY, signed char rightY){
        left_g.move(abs(leftY)<threshold ? 0 :leftY);
        right_g.move(abs(rightY)<threshold ? 0 :rightY);
    }

    inline void arcadeDrive(signed char leftY, signed char rightX) {
        leftY = abs(leftY)<threshold ? 0 : leftY;
        rightX = abs(rightX)<threshold ? 0 : rightX;
        left_g.move(leftY + rightX);
        right_g.move(leftY - rightX);
    }

    //This code is from Darshaan Karthikeyan (597C)
    //Function allows for the forward and backward motion of the drivetrain based on the given inches
    inline void moveHorizontal(double inches){
    // Apply the calibration factor as a divisor: distancePerTickFactor was
    // recorded as commanded/measured, so we divide to get the effective
    // inches-per-tick to use when converting inches -> ticks.
    double effDistancePerTick = distancePerTick / distancePerTickFactor;
    int ticksToMove = static_cast<int>(std::round((inches)/effDistancePerTick));

        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();

        left_g.move_relative(ticksToMove, maxRPM);
        right_g.move_relative(ticksToMove, maxRPM);
        
        // Wait until both sides have reached (or exceeded) the target ticks.
        while (std::abs(left_g.get_position()) < std::abs(ticksToMove) || std::abs(right_g.get_position()) < std::abs(ticksToMove)) {
            delay(20); // Prevents busy waiting
        }

        left_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        delay(delayMove);
    }

    //Function turns the robot by a relative angle (degrees).
    //Positive `angle` turns clockwise (increasing heading), negative turns counter-clockwise.
    //Uses IMU heading read via `imu_get_heading(10)` and a simple P-controller.
    inline void turnAngle(double angle){
        const double headingTolerance = 1.0; // degrees tolerance to stop

        // Helper: compute shortest signed difference target - current in range [-180,180]
        auto angleError = [](double target, double current) {
            double diff = fmod((target - current + 540.0), 360.0) - 180.0; // maps to [-180,180]
            return diff;
        };

    // Read current heading from IMU
    double current = imu_get_heading(DRIVE_IMU_PORT);

        // Compute absolute target heading (wrap into [0,360))
        double target = fmod(current + angle + 360.0, 360.0);

        double error = angleError(target, current);

        // If angle is effectively zero, return early
        if (std::fabs(angle) < 1e-6) return;

        // Simple P-control using a dedicated heading_kP; clamp command to heading_maxRPM
        while (std::fabs(error) > headingTolerance) {
            double command = heading_kP * error; // proportional control (use heading_kP)

            // clamp to allowable motor velocity range for turning
            if (command > heading_maxRPM) command = heading_maxRPM;
            if (command < -heading_maxRPM) command = -heading_maxRPM;

            // If command is very small but we are not inside tolerance, boost to a minimum RPM
            if (std::fabs(command) < heading_minRPM) {
                command = (command >= 0) ? heading_minRPM : -heading_minRPM;
            }

            left_g.move_velocity(command);
            right_g.move_velocity(-command);

            delay(20);

            current = imu_get_heading(DRIVE_IMU_PORT);
            error = angleError(target, current);
        }

        // stop motors
        left_g.move_velocity(0);
        right_g.move_velocity(0);

        delay(delayMove);
    }

    inline void turnAngleNew(double angle, signed char Direction){
        double distanceTravel = ((trackwidth)*angle*pi)/(360.0*2.0);
        int ticks = distanceTravel/distancePerTick;

        //Reseting the position of the left and right group of motorsp
        left_g.tare_position();
        right_g.tare_position();
        
        left_g.move_relative(Direction * ticks, maxRPM);
        right_g.move_relative(Direction * -(ticks), maxRPM);

        while (std::abs(left_g.get_position()) <= abs(ticks) && std::abs(right_g.get_position()) <= abs(ticks)) {
            delay(20); // Prevents busy waiting
        }

        delay(delayMove);
    }

    inline void turnAngle_sohan(signed char turnAngle) {
        left_g.tare_position();
        right_g.tare_position();

        double arc_length = ((turnAngle*pi*radius)/180) ;
        double theta = arc_length/radius;

        double error = arc_length;
        double prevError = error;
        double proportional = 0;
        double integral = 0;
        double derivative = 0;

        while (fabs(error) >= 1.0) {
            proportional = error;
            integral += error;
            derivative = prevError - error;

            double speed = proportional * kP + integral * kI + derivative * kD;
            left_g.move(speed);
            right_g.move(-speed);
            error = left_g.get_position() - right_g.get_position();
            error /= 2;
            error *= radius *  pi / 180.0;
            error = arc_length - error;
        }
        left_g.move(0);
        right_g.move(0);
    }

    inline void moveForward(signed char moveAmount) {
        left_g.move_relative(moveAmount,100);
        right_g.move_relative(moveAmount,100);
    }

    inline void moveBackward(signed char moveAmount) {
        // 360 
        // 5 : 3
        float rotations = moveAmount * 5 / 3;
        float circumference = 3.25 * pi;
        int ticks = rotations * circumference;
        left_g.move_absolute(ticks, 100);
        left_g.move_absolute(ticks, 100);
    }
 
    inline void moveHorizontal(double inches, int32_t velocity){
    // See comment above in the single-arg overload.
    double effDistancePerTick = distancePerTick / distancePerTickFactor;
    int ticksToMove = static_cast<int>(std::round((inches)/effDistancePerTick));

    // Debug info: print target and computed ticks
    printf("[DriveTrain] moveHorizontal target: %.2f inches -> ticksToMove: %d\n", inches, ticksToMove);


        //Reseting the position of the left and right group of motors
        left_g.tare_position();
        right_g.tare_position();


        left_g.move_relative(ticksToMove, velocity);
        right_g.move_relative(ticksToMove, velocity);
       
        // Wait until both sides have reached (or exceeded) the target ticks.
        int dbgCounter = 0;
        while (std::abs(left_g.get_position()) < std::abs(ticksToMove) || std::abs(right_g.get_position()) < std::abs(ticksToMove)) {
            // Print motor positions occasionally to help debug distance scaling
            if ((dbgCounter++ % 10) == 0) {
                int leftPos = left_g.get_position();
                int rightPos = right_g.get_position();
                double leftIn = leftPos * effDistancePerTick;
                double rightIn = rightPos * effDistancePerTick;
                printf("[DriveTrain] pos L=%d(%.2fin) R=%d(%.2fin)\n", leftPos, leftIn, rightPos, rightIn);
            }
            delay(20); // Prevents busy waiting
        }


        left_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


    double leftPos = left_g.get_position();
    double rightPos = right_g.get_position();
    printf("[DriveTrain] final L=%d(%.2fin) R=%d(%.2fin)\n", (int)leftPos, leftPos*effDistancePerTick, (int)rightPos, rightPos*effDistancePerTick);
        delay(delayMove);
    }

    // Move using IMU acceleration integration to estimate distance.
    // Notes:
    // - This uses the IMU's X-axis accelerometer (forward axis) and integrates
    //   acceleration to estimate velocity and distance. The IMU reports
    //   acceleration in m/s^2; this method converts to inches/s^2 using
    //   MS2_TO_IN_S2.
    // - IMU accelerometers are noisy and susceptible to drift; expect this to
    //   need calibration (and possibly filtering) for reliable distance.
    inline void moveHorizontalIMU(double inches, int32_t velocity){

    // Use tunable constants from Constants.hpp
    const double MS2_TO_IN_S2 = imu_ms2_to_in_s2 * imu_calibration_scale;

    // simple integration parameters (from Constants)
    const double dt = imu_dt; // seconds (20 ms sampling)
    const double alpha = imu_alpha; // simple low-pass for accel

        double target = inches;
        int dir = (target >= 0) ? 1 : -1;

        left_g.tare_position();
        right_g.tare_position();

        // start driving at requested velocity
        left_g.move_velocity(dir * velocity);
        right_g.move_velocity(dir * velocity);

    double s = 0.0; // distance in inches
    double v = 0.0; // velocity in inches/s (estimated)
    double last_a = 0.0;

    // safety timeout from constants
    const int maxLoops = static_cast<int>(imu_timeout / dt);
        int loops = 0;

        int imuDbg = 0;
        printf("[DriveTrain] moveHorizontalIMU target: %.2f inches\n", target);
        while (std::fabs(s) < std::fabs(target) && loops < maxLoops) {
            double ax = imu_get_accel_x(DRIVE_IMU_PORT); // m/s^2
            double a_in = ax * MS2_TO_IN_S2; // convert to in/s^2

            // low-pass filter to reduce noise
            double a_f = alpha * a_in + (1.0 - alpha) * last_a;

            // integrate (trapezoid approx simplified)
            v += a_f * dt;
            s += v * dt + 0.5 * a_f * dt * dt;

            last_a = a_f;

            // Print debug info per configured interval
            if ((imuDbg++ % imu_debug_interval_loops) == 0) {
                printf("[DriveTrain][IMU] a=%.3f in/s^2 v=%.3f in/s s=%.3f in\n", a_f, v, s);
            }
            delay(static_cast<int>(dt * 1000));
            loops++;
        }

        // stop motors
        left_g.move_velocity(0);
        right_g.move_velocity(0);

        left_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        delay(delayMove);
    }

    // Calibration helper: command a known distance (inches) and report encoder ticks
    // and the empirical inches/tick. Use this to compute a corrected distancePerTick.
    inline void calibrateDistance(double commanded_inches, int32_t velocity) {
        printf("[DriveTrain] calibrateDistance: commanding %.2f inches at vel=%d\n", commanded_inches, velocity);

    // Invert previous incorrect multiplication: factor was stored as
    // commanded/measured, so divide to compute effective inches/tick.
    double effDistancePerTick = distancePerTick / distancePerTickFactor;
        // compute ticks requested using effective distancePerTick
        int ticksToMove = static_cast<int>(std::round((commanded_inches)/effDistancePerTick));

        left_g.tare_position();
        right_g.tare_position();

        left_g.move_relative(ticksToMove, velocity);
        right_g.move_relative(ticksToMove, velocity);

        // wait until both sides have reached target
        while (std::abs(left_g.get_position()) < std::abs(ticksToMove) || std::abs(right_g.get_position()) < std::abs(ticksToMove)) {
            delay(20);
        }

        int leftTicks = left_g.get_position();
        int rightTicks = right_g.get_position();
    double leftIn = leftTicks * effDistancePerTick;
    double rightIn = rightTicks * effDistancePerTick;
        double avgTicks = (std::abs(leftTicks) + std::abs(rightTicks)) / 2.0;
        double empirical_inches_per_tick = commanded_inches / avgTicks;

        printf("[DriveTrain] calibrate result: L_ticks=%d R_ticks=%d L_in=%.2f R_in=%.2f\n", leftTicks, rightTicks, leftIn, rightIn);
        printf("[DriveTrain] empirical inches/tick = %.8f (current distancePerTick=%.8f)\n", empirical_inches_per_tick, distancePerTick);
        printf("[DriveTrain] Suggested new distancePerTick = %.8f (replace in Constants.hpp)\n", empirical_inches_per_tick);

        left_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        delay(delayMove);
    }



};
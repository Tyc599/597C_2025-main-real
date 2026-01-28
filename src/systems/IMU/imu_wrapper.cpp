// Simple wrapper to provide a C++-linkable function `imu_get_heading(uint8_t)`
// so other code (e.g. DriveTrain) can call it and the linker has a definition.
// This file creates and caches a pros::Imu per port on first use.

#include "pros/imu.hpp"
#include "pros/imu.h"
#include <cstdint>
#include <map>
#include <memory>

double imu_get_heading(uint8_t port) {
    // Cache Imu instances per port so we don't repeatedly construct/destroy them.
    static std::map<uint8_t, std::unique_ptr<pros::Imu>> instances;

    auto it = instances.find(port);
    if (it == instances.end()) {
        // Construct a new pros::Imu for this port and store it.
        instances[port] = std::make_unique<pros::Imu>(port);
        it = instances.find(port);
    }

    // Return heading in degrees. pros::Imu::get_heading() returns a double.
    return it->second->get_heading();
}

// Return the IMU's raw accelerometer X-axis (forward) value for the given port.
// Use the C API `imu_get_accel(port)` (declared in pros/imu.h) which returns
// the accelerometer struct. This avoids creating an extra pros::Imu instance.
double imu_get_accel_x(uint8_t port) {
    // The C API function is placed in the pros::c namespace in these headers.
    auto accel = pros::c::imu_get_accel(port); // imu_accel_s_t
    return accel.x;
}

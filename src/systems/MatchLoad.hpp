#pragma once

#include "pros/motors.hpp"
#include "../systems/Constants.hpp"

#include "../../include/pros/adi.hpp"

using namespace Constants;
using namespace pros;
using namespace adi;

struct MatchLoad {
    private:
        DigitalOut piston = DigitalOut(hinge_a);

    public:
        MatchLoad() {
        }

        void up() {
            piston.set_value(false);
        }

        void down() {
            piston.set_value(true);
        }

        void changeLoadState(bool newState) {
            piston.set_value(newState);
        }

};
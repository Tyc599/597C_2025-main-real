#pragma once

#include "../Constants.hpp"
#include "pros/optical.hpp"
#include "pros/vision.hpp"

namespace ColorSort {

// Small struct that holds certainty values in the range [0,1].
// presence: probability/confidence that there's a block present
// red: probability/confidence that the object is red
// blue: probability/confidence that the object is blue
struct ColorCertainty {
    double presence = 0.0;
    double red = 0.0;
    double blue = 0.0;
};

// Analyze optical sensor readings and produce certainties.
// Uses: optical_get_proximity, optical_get_hue, optical_get_saturation
// Heuristics are intentionally conservative and documented in the .cpp.
ColorCertainty analyzeOptical(uint8_t optical_port);

// Analyze the largest vision object by size and also optionally probe
// for specific color codes. Pass `min_area` to scale presence certainty.
// If you have pre-configured color codes for red/blue use them, otherwise
// pass 0 to skip color-code checks.
ColorCertainty analyzeVisionBySize(uint8_t vision_port, uint32_t min_area, pros::vision_color_code_t red_code = 0,
                                  pros::vision_color_code_t blue_code = 0);

// Merge two independent certainties (optical + vision). `optical_weight`
// controls how much to trust optical sensor (0..1). Returns combined cert.
ColorCertainty mergeCertainties(const ColorCertainty& optical, const ColorCertainty& vision,
                                double optical_weight = 0.5);


// Example usage:
//
//    // Optical sensor on port 7, vision on port 8. If you configured
//    // color codes via the Vision utility, pass them; otherwise pass 0.
//    auto opt = ColorSort::analyzeOptical(7);
//    auto vis = ColorSort::analyzeVisionBySize(8, 1000, 0, 0);
//    auto combined = ColorSort::mergeCertainties(opt, vis, 0.6);
//
//    // combined.presence, combined.red, combined.blue are in [0,1]


} // namespace ColorSort

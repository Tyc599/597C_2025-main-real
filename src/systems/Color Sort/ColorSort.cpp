#include "ColorSort.hpp"

using namespace ColorSort;

static inline double clamp01(double v) {
    if (v < 0.0) return 0.0;
    if (v > 1.0) return 1.0;
    return v;
}

// Map a hue distance to a certainty (simple linear falloff).
// center: expected hue center (0-360), tol: half-width where certainty falls to 0
static double hueDistanceCertainty(double hue, double center, double tol) {
    // normalize
    double d = fabs(hue - center);
    // allow wrap around at 360
    if (d > 180.0) d = 360.0 - d;
    double cert = 1.0 - (d / tol);
    return clamp01(cert);
}

ColorCertainty ColorSort::analyzeOptical(uint8_t optical_port) {
    ColorCertainty out;

    // Read sensors via C++ PROS wrappers
    pros::Optical optical(optical_port);
    double prox = static_cast<double>(optical.get_proximity()); // 0..255
    double hue = optical.get_hue();       // 0..360
    double sat = optical.get_saturation(); // 0..1
    double bright = optical.get_brightness(); // 0..1

    // Presence: rely mainly on proximity and brightness. Normalize prox -> [0,1]
    double prox_norm = clamp01(prox / 255.0);
    double brightness_factor = clamp01(bright);
    // combine: give proximity more weight, but multiply by brightness
    out.presence = clamp01(0.8 * prox_norm + 0.2 * (sat)) * brightness_factor;

    // If presence is nearly zero, early exit with zeros for color.
    if (out.presence < 0.05) return out;

    // Heuristic hue centers. These are intentionally broad; tune if needed.
    // Red is around 0 (wrap-around), allow tol ~ 40 degrees
    double red_cert = hueDistanceCertainty(hue, 0.0, 40.0);
    // Blue typical center ~210 degrees (VEX/HSV), tol ~ 50
    double blue_cert = hueDistanceCertainty(hue, 210.0, 50.0);

    // Weight by saturation (low saturation -> less color confidence)
    red_cert *= clamp01(sat);
    blue_cert *= clamp01(sat);

    // Scale color certainties by presence to keep them consistent
    out.red = clamp01(red_cert * out.presence);
    out.blue = clamp01(blue_cert * out.presence);

    return out;
}

ColorCertainty ColorSort::analyzeVisionBySize(uint8_t vision_port, uint32_t min_area,
                                              pros::vision_color_code_t red_code, pros::vision_color_code_t blue_code) {
    ColorCertainty out;

    // Get the largest object by size (0 = largest). If none, vision_get_by_size may
    // return a struct with signature == VISION_OBJECT_ERR_SIG (255 macro), treat that
    // as no object.
    pros::Vision vision(vision_port);
    pros::vision_object_s_t obj = vision.get_by_size(0);

    const uint32_t err_sig = VISION_OBJECT_ERR_SIG;

    if (obj.signature == err_sig) {
        // no object detected or error
        out.presence = 0.0;
    } else {
        // size is width*height; scale presence by requested min_area
        uint32_t area = static_cast<uint32_t>(static_cast<uint32_t>(obj.width) * static_cast<uint32_t>(obj.height));
        if (min_area == 0) min_area = 1; // avoid divide-by-zero
        double pres = static_cast<double>(area) / static_cast<double>(min_area);
        out.presence = clamp01(pres);
    }

    // Color-code checks (if user has created color codes in the Vision utility)
    // If codes are not provided (0), skip these checks.
    double red_cert = 0.0;
    double blue_cert = 0.0;

    if (red_code != 0) {
    pros::vision_object_s_t red_obj = vision.get_by_code(0, red_code);
        if (red_obj.signature != err_sig) {
            uint32_t area = static_cast<uint32_t>(static_cast<uint32_t>(red_obj.width) * static_cast<uint32_t>(red_obj.height));
            double pres = static_cast<double>(area) / static_cast<double>(min_area);
            red_cert = clamp01(pres);
        }
    }

    if (blue_code != 0) {
    pros::vision_object_s_t blue_obj = vision.get_by_code(0, blue_code);
        if (blue_obj.signature != err_sig) {
            uint32_t area = static_cast<uint32_t>(static_cast<uint32_t>(blue_obj.width) * static_cast<uint32_t>(blue_obj.height));
            double pres = static_cast<double>(area) / static_cast<double>(min_area);
            blue_cert = clamp01(pres);
        }
    }

    // If color codes were not provided, attempt a best-effort guess from the
    // default signature of the largest object (some teams configure signatures for
    // red/blue -- this is only a heuristic).
    if (red_code == 0 && blue_code == 0 && out.presence > 0.0 && obj.signature != err_sig) {
        // Very simple heuristic: many teams use signature ids 1..7. We won't assume mapping,
        // but we provide a tiny fallback: if signature is odd assume red, even assume blue.
        if ((obj.signature % 2) == 1) {
            red_cert = out.presence * 0.9;
        } else {
            blue_cert = out.presence * 0.9;
        }
    }

    // Finalize values scaled by presence
    out.red = clamp01(red_cert * out.presence);
    out.blue = clamp01(blue_cert * out.presence);

    return out;
}

ColorCertainty ColorSort::mergeCertainties(const ColorCertainty& optical, const ColorCertainty& vision,
                                           double optical_weight) {
    ColorCertainty out;
    double w_opt = clamp01(optical_weight);
    double w_vis = clamp01(1.0 - w_opt);

    out.presence = clamp01(optical.presence * w_opt + vision.presence * w_vis);
    out.red = clamp01(optical.red * w_opt + vision.red * w_vis);
    out.blue = clamp01(optical.blue * w_opt + vision.blue * w_vis);
    return out;
}

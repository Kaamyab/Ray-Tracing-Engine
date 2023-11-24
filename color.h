#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    return sqrt(linear_component);
}

void calc_color(unsigned int* pixel, color pixel_color, int samples_per_pixel)
{
    static const interval intensity(0.000, 0.999);
    pixel[0] = static_cast<int>(256 * intensity.clamp((pixel_color.x() *(1.0 / samples_per_pixel))));
    pixel[1] = static_cast<int>(256 * intensity.clamp((pixel_color.y() *(1.0 / samples_per_pixel))));
    pixel[2] = static_cast<int>(256 * intensity.clamp((pixel_color.z() *(1.0 / samples_per_pixel))));
    // std::cout << pixel[0] << " " << pixel[1] << " " << pixel[2] << std::endl;
}

#endif
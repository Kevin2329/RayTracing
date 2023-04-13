//
// Created by 17912 on 2023/4/11.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "vec3.h"
#include"rtweekend.h"
#include <fstream>

void write_color(std::fstream &f, color &pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    double scale = 1.0 / samples_per_pixel;
    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    f << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' ' << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';

}

#endif //RAYTRACING_COLOR_H

//
// Created by 17912 on 2023/4/11.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "vec3.h"
#include <fstream>

void write_color(std::fstream &f, color pixel_color)
{
    f << static_cast<int>(255.999 * pixel_color.x()) << ' '
      << static_cast<int>(255.999 * pixel_color.y()) << ' '
      << static_cast<int>(255.999 * pixel_color.z()) << '\n';

}

#endif //RAYTRACING_COLOR_H

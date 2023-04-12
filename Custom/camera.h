//
// Created by 17912 on 2023/4/12.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include"rtweekend.h"

class camera
{
public:
    camera()
    {
        const auto aspect_ratio = 16.0 / 9.0;
        const auto viewport_width = 4.0;
        const auto viewport_height = viewport_width / aspect_ratio;
        auto focal_length = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0, 0);
        vertical = vec3(0, viewport_height, 0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
    }

    ray get_ray(double u, double v)
    {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

};


#endif //RAYTRACING_CAMERA_H

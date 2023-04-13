//
// Created by 17912 on 2023/4/11.
//

#ifndef RAYTRACING_RTWEEKEND_H
#define RAYTRACING_RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

/// Returns a random real in [0,1)
inline double random_double()
{
    return double(rand()) / (RAND_MAX + 1);
}

/// Returns a random real in [min,max]
inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

inline static vec3 random_unit_sphere()
{
    auto p = vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
    p= unit_vector(p);
    return p;

}

// Common Headers

#include "ray.h"
#include "vec3.h"


#endif //RAYTRACING_RTWEEKEND_H

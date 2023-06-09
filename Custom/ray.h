//
// Created by 17912 on 2023/4/11.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include"vec3.h"

class ray
{
public:
    ray(){}
    ray(const point3 &origin, const vec3 &direction, double time=0.0)
        : orig(origin), dir(direction),tm(time)
    {}

    point3 origin() const
    {
        return orig;
    }

    vec3 direction() const
    {
        return dir;
    }

    point3 at(double t) const
    {
        return orig + t * dir;
    }

    double time() const
    {
        return tm;
    }
private :
    point3 orig;
    vec3 dir;
    double tm;


};

#endif //RAYTRACING_RAY_H

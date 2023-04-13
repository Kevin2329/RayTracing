//
// Created by 17912 on 2023/4/13.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include"ray.h"

struct hit_record;

class material
{
public:
    virtual bool scatter(const ray &ray_in, const hit_record &rec, color &attenuation, ray &ray_out) const = 0;


};

#endif //RAYTRACING_MATERIAL_H

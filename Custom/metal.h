//
// Created by 17912 on 2023/4/13.
//

#ifndef RAYTRACING_METAL_H
#define RAYTRACING_METAL_H

#include"material.h"

class metal : public material
{
public:
    metal(const color &albedo) : albedo(albedo)
    {}

    bool scatter(const ray &ray_in, const hit_record &rec, color &attenuation, ray &ray_out) const override
    {
        auto ray_out_direction = reflect(ray_in.direction(), rec.normal);
        ray_out = ray(rec.p, ray_out_direction);
        attenuation = albedo;
        return (dot(ray_out_direction, rec.normal) > 0);
    }

private:
    color albedo;
};


#endif //RAYTRACING_METAL_H

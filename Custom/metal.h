//
// Created by 17912 on 2023/4/13.
//

#ifndef RAYTRACING_METAL_H
#define RAYTRACING_METAL_H

#include"material.h"

class metal : public material
{
public:
    metal(const color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1)
    {};

    bool scatter(const ray &ray_in, const hit_record &rec, color &attenuation, ray &ray_out) const override
    {
        auto ray_out_direction = reflect(ray_in.direction(), rec.normal) + fuzz * random_unit_sphere();
        ray_out = ray(rec.p, ray_out_direction);
        attenuation = albedo;
        return (dot(ray_out_direction, rec.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};


#endif //RAYTRACING_METAL_H

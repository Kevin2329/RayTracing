//
// Created by 17912 on 2023/4/13.
//

#ifndef RAYTRACING_LAMBERTIAN_H
#define RAYTRACING_LAMBERTIAN_H

#include"material.h"
#include"rtweekend.h"

class lambertian : public material
{
public:
    lambertian(const color &albedo) : albedo(albedo)
    {}

    bool scatter(const ray &ray_in, const hit_record &rec, color &attenuation, ray &ray_out) const override
    {
        auto ray_out_direction = rec.p + random_unit_hemisphere(rec.normal);
        ray_out = ray(rec.p, ray_out_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};


#endif //RAYTRACING_LAMBERTIAN_H

//
// Created by 17912 on 2023/4/14.
//

#ifndef RAYTRACING_DIELECTRIC_H
#define RAYTRACING_DIELECTRIC_H

#include"material.h"

class dielectric : public material
{
public:
    dielectric(double refractive_index) : refractive_index(refractive_index)
    {}

    bool scatter(const ray &ray_in, const hit_record &rec, color &attenuation, ray &ray_out) const override
    {
        attenuation = color(1, 1, 1);
        double refractive_index_ratio = rec.front_face ? (1.0 / refractive_index) : refractive_index;
        auto unit_direction = unit_vector(ray_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refractive_index_ratio * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refractive_index_ratio) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refractive_index_ratio);

        ray_out = ray(rec.p, direction,ray_in.time());
        return true;
    }

private:
    double refractive_index;

private:
    static double reflectance(double cosine, double ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};


#endif //RAYTRACING_DIELECTRIC_H

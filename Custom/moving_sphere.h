//
// Created by 常凯文 on 2023/4/17.
//

#ifndef RAYTRACING_MOVING_SPHERE_H
#define RAYTRACING_MOVING_SPHERE_H

#include"hittable.h"
#include"rtweekend.h"


class moving_sphere : public hittable
{
public:
    moving_sphere()
    {}

    moving_sphere(const point3 cen0, const point3 cen1, double t0, double t1,
                  double r, shared_ptr<material> m) :
            center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m)
    {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    point3 center(double time) const
    {
        return center0 + (center1 - center0) * ((time - time0) / (time1 - time0));
    }

private:
    point3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<material> mat_ptr;
};

bool moving_sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.mat_ptr = mat_ptr;
    vec3 outward_normal = (rec.p - center(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}




#endif //RAYTRACING_MOVING_SPHERE_H

//
// Created by 17912 on 2023/4/11.
//

#ifndef RAYTRACING_HITTABLE_LIST_H
#define RAYTRACING_HITTABLE_LIST_H

#include<vector>
#include<memory>

#include"hittable.h"

using std::shared_ptr;

class hittable_list : hittable
{
public:
    hittable_list()
    {}

    hittable_list(shared_ptr<hittable> object)
    {
        add(object);
    }

    void clear()
    {
        objects.clear();
    }

    void add(shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_record;
    bool hit_anything = false;
    double minDistance_squared = std::numeric_limits<double>::max();
    for (auto &object: objects)
    {
        if (object->hit(r, t_min, t_max, temp_record))
        {
            hit_anything = true;
            auto distance_squared = (temp_record.p - r.origin()).length_squared();
            //the hit point is closest to the ray's origin
            if (minDistance_squared > distance_squared)
            {
                rec = temp_record;
                minDistance_squared = distance_squared;
            }
        }
    }
    return hit_anything;


}


#endif //RAYTRACING_HITTABLE_LIST_H

#include <iostream>
#include "Custom/color.h"
#include "Custom/vec3.h"
#include"Custom/ray.h"
#include "Custom/rtweekend.h"
#include"Custom/hittable.h"
#include"Custom/hittable_list.h"
#include"Custom/sphere.h"
#include"Custom/camera.h"

color ray_color(const ray &r, const hittable_list &world, int depth)
{
    if (depth <= 0)
        return color(0, 0, 0);
    hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        point3 target = rec.p + rec.normal + random_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());//y  is between -1~1
    auto t = 0.5 * unit_direction.y() + 0.5;
    return color(1, 1, 1) * (1 - t) + color(0.5, 0.7, 1.0) * t;

}

int main()
{
    std::fstream image("E:/RayTracing/image.ppm", std::ios::out | std::ios::trunc);
    const int maxDepth = 50;

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    //world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));


    //camera
    camera cam;

    // Render

    image << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color pixelColor(0, 0, 0);
            for (int k = 0; k < samples_per_pixel; ++k)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixelColor += ray_color(r, world, maxDepth);
            }
            write_color(image, pixelColor, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}
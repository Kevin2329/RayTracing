#include <iostream>
#include "Custom/color.h"
#include "Custom/vec3.h"
#include"Custom/ray.h"
#include "Custom/rtweekend.h"
#include"Custom/hittable.h"
#include"Custom/hittable_list.h"
#include"Custom/sphere.h"
#include"Custom/camera.h"
#include"Custom/material.h"
#include"Custom/lambertian.h"
#include"Custom/metal.h"
#include"Custom/dielectric.h"
#include"Custom/moving_sphere.h"

color ray_color(const ray &r, const hittable_list &world, int depth)
{
    if (depth <= 0)
        return color(0, 0, 0);
    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec))
    {
        ray ray_out;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, ray_out))
        {
            return attenuation * ray_color(ray_out, world, depth - 1);
        }
        return color(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());//y  is between -1~1
    auto t = 0.5 * unit_direction.y() + 0.5;
    return color(1, 1, 1) * (1 - t) + color(0.5, 0.7, 1.0) * t;

}
hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -2; a < 2; a++) {
        for (int b = -2; b < 2; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_color() * random_color();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                            center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_color(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

int main()
{
    std::fstream image("/Users/kevin/Desktop/RayTracing/cmake-build-debug/image.ppm", std::ios::out | std::ios::trunc);
    if(!image.is_open())
        throw std::runtime_error("failed to open files!");
    const int maxDepth = 50;

    // Image
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    //world
    auto world = random_scene();

    //camera
    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus,0.0,1.0);

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
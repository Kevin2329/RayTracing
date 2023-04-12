#include <iostream>
#include "Custom/color.h"
#include "Custom/vec3.h"
#include"Custom/ray.h"
#include "Custom/rtweekend.h"
#include"Custom/hittable.h"
#include"Custom/hittable_list.h"
#include"Custom/sphere.h"

color ray_color(const ray &r, const hittable_list &world)
{
    hit_record rec;
    for (auto &obj: world.objects)
        if (obj->hit(r, 0, infinity, rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }
    vec3 unit_direction = unit_vector(r.direction());//y is between -1~1
    auto t = 0.5 * unit_direction.y() + 0.5;
    return color(1, 1, 1) * (1 - t) + color(0.5, 0.7, 1.0) * t;

}

int main()
{
    std::fstream image("E:/RayTracing/image.ppm");

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //camera
    const auto viewport_width = 4.0;
    const auto viewport_height = viewport_width / aspect_ratio;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);


    // Render

    image << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {

            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);

            color pixel_color = ray_color(r, world);
            write_color(image, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}
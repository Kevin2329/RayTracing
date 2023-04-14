cmake_minimum_required(VERSION 3.24)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing main.cpp Custom/vec3.h Custom/color.h Custom/ray.h Custom/hittable.h Custom/sphere.h Custom/hittable_list.h Custom/rtweekend.h Custom/camera.h Custom/material.h Custom/lambertian.h Custom/metal.h Custom/dielectric.h)

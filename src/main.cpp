#include <iostream>
#include <memory>

#include "Camera.h"
#include "HitList.h"
#include "HitSphere.h"
#include "Material.h"

int main() {
  // World
  HitList world;

  auto lambertian_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto lambertian_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
  auto dielectric_left = std::make_shared<Dielectric>(1.50);
  auto metal_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.1);

  world.Add(std::make_shared<HitSphere>(Point3(0.0, -100.5, -1.0), 100.0, lambertian_ground));
  world.Add(std::make_shared<HitSphere>(Point3(0.0, 0.0, -1.2), 0.5, lambertian_center));
  world.Add(std::make_shared<HitSphere>(Point3(-1.0, 0.0, -1.0), 0.5, dielectric_left));
  world.Add(std::make_shared<HitSphere>(Point3(1.0, 0.0, -1.0), 0.5, metal_right));

  std::unique_ptr<Camera> camera = std::make_unique<Camera>();

  camera->aspect_ratio = 16.0 / 9.0;
  camera->image_width = 1000;
  camera->samples_per_pixel = 20;
  camera->max_depth = 10;

  camera->Render(world);
}

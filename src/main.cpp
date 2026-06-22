#include <iostream>
#include <memory>

#include "Camera.h"
#include "HitList.h"
#include "HitSphere.h"

int main() {
  // World
  HitList world;
  world.Add(std::make_shared<HitSphere>(Point3(0, 0, -1), 0.5));
  world.Add(std::make_shared<HitSphere>(Point3(0, -100.5, -1), 100));

  Camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;

  cam.Render(world);
}

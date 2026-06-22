#pragma once

#include "Color.h"
#include "HitBase.h"

class Camera {
 public:
  double aspect_ratio = 1.0;  // Ratio of image width over height
  int image_width = 100;      // Rendered image width in pixel count

  void Render(const HitBase& world);

 private:
  int image_height_;   // Rendered image height
  Point3 center_;      // Camera center
  Point3 pixel00_loc;  // Location of pixel 0, 0
  Vec3 pixel_delta_u;  // Offset to pixel to the right
  Vec3 pixel_delta_v;  // Offset to pixel below

  void Initialize();

  Color RayColor(const Ray& r, const HitBase& world) const;
};
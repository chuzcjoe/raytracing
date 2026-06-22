#pragma once

#include "Color.h"
#include "HitBase.h"

class Camera {
 public:
  double aspect_ratio = 1.0;   // Ratio of image width over height
  int image_width = 100;       // Rendered image width in pixel count
  int samples_per_pixel = 10;  // Count of random samples for each pixel

  void Render(const HitBase& world);

 private:
  int image_height_;            // Rendered image height
  Point3 center_;               // Camera center
  Point3 pixel00_loc;           // Location of pixel 0, 0
  Vec3 pixel_delta_u;           // Offset to pixel to the right
  Vec3 pixel_delta_v;           // Offset to pixel below
  double pixel_samples_scale_;  // Color scale factor for a sum of pixel samples

  void Initialize();

  Ray GetRay(int i, int j) const;

  Vec3 SampleSquare() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  Color RayColor(const Ray& r, const HitBase& world) const;
};
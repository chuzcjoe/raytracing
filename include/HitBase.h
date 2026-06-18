#pragma once

#include "Ray.h"

class HitRecord {
 public:
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;

  void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class HitBase {
 public:
  virtual ~HitBase() = default;

  virtual bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};
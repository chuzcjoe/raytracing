#pragma once

#include "Interval.h"
#include "Ray.h"

class Material;

class HitRecord {
 public:
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;
  std::shared_ptr<Material> material;

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

  virtual bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};
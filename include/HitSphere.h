#pragma once

#include "HitBase.h"
#include "Material.h"

class HitSphere : public HitBase {
 public:
  HitSphere(const Point3& center, const double radius, std::shared_ptr<Material> material);

  bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

 private:
  Point3 center_;
  double radius_;
  std::shared_ptr<Material> material_;
};
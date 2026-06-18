#pragma once

#include "HitBase.h"

class HitSphere : public HitBase {
 public:
  HitSphere(const Point3& center, double radius);

  bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;

 private:
  Point3 center_;
  double radius_;
};
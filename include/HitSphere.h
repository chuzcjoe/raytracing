#pragma once

#include "HitBase.h"

class HitSphere : public HitBase {
 public:
  HitSphere(const Point3& center, double radius);

  bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

 private:
  Point3 center_;
  double radius_;
};
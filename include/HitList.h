#pragma once

#include <memory>
#include <vector>

#include "HitBase.h"

class HitList : public HitBase {
 public:
  std::vector<std::shared_ptr<HitBase>> hit_objects;

  HitList() = default;
  HitList(std::shared_ptr<HitBase> object) { Add(object); }

  void Clear() { hit_objects.clear(); }

  void Add(std::shared_ptr<HitBase> object) { hit_objects.push_back(object); }

  bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};
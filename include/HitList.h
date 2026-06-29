#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "HitBase.h"

class HitList : public HitBase {
 public:
  std::vector<std::shared_ptr<HitBase>> hit_objects;

  HitList() = default;
  HitList(std::shared_ptr<HitBase> object) { Add(std::move(object)); }

  void Clear() { hit_objects.clear(); }

  void Add(std::shared_ptr<HitBase> object) { hit_objects.push_back(std::move(object)); }

  bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};

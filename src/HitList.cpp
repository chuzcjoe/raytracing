#include "HitList.h"

bool HitList::Hit(const Ray& r, Interval ray_t, HitRecord& rec) const {
  HitRecord temp_rec;
  bool hit_anything = false;
  auto closest_so_far = ray_t.max;

  for (const auto& object : hit_objects) {
    if (object->Hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}
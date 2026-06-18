#include "HitList.h"

bool HitList::Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const {
  HitRecord temp_rec;
  bool hit_anything = false;
  auto closest_so_far = ray_tmax;

  for (const auto& object : hit_objects) {
    if (object->Hit(r, ray_tmin, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}
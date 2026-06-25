#include "HitSphere.h"

HitSphere::HitSphere(const Point3& center, const double radius, std::shared_ptr<Material> material)
    : center_(center), radius_(std::fmax(0, radius)), material_(material) {
    // init material
  }

bool HitSphere::Hit(const Ray& r, Interval ray_t, HitRecord& rec) const {
  Vec3 oc = center_ - r.origin();
  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius_ * radius_;

  auto discriminant = h * h - a * c;
  if (discriminant < 0) return false;

  auto sqrtd = std::sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (h - sqrtd) / a;
  if (!ray_t.surrounds(root)) {
    root = (h + sqrtd) / a;
    if (!ray_t.surrounds(root)) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  Vec3 outward_normal = (rec.p - center_) / radius_;
  rec.SetFaceNormal(r, outward_normal);
  rec.material = material_;

  return true;
}

#include "HitSphere.h"

HitSphere::HitSphere(const Point3& center, double radius)
    : center_(center), radius_(std::fmax(0, radius)) {}

bool HitSphere::Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const {
  Vec3 oc = center_ - r.origin();
  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius_ * radius_;

  auto discriminant = h * h - a * c;
  if (discriminant < 0) return false;

  auto sqrtd = std::sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (h - sqrtd) / a;
  if (root <= ray_tmin || ray_tmax <= root) {
    root = (h + sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  Vec3 outward_normal = (rec.p - center_) / radius_;
  rec.SetFaceNormal(r, outward_normal);
  rec.normal = (rec.p - center_) / radius_;

  return true;
}
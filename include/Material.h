#pragma once

#include "Color.h"
#include "HitBase.h"

class Material {
 public:
  virtual ~Material() = default;

  virtual bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation,
                       Ray& ray_scattered) const = 0;
};

class Lambertian : public Material {
 public:
  Lambertian(const Color& albedo) : albedo_(albedo) {}

  bool Scatter(const Ray&, const HitRecord& rec, Color& attenuation,
               Ray& ray_scattered) const override {
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    ray_scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo_;
    return true;
  }

 private:
  Color albedo_;
};

class Metal : public Material {
 public:
  Metal(const Color& albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz) {}

  bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation,
               Ray& ray_scattered) const override {
    Vec3 reflected = reflect(ray_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz_ * random_unit_vector());
    ray_scattered = Ray(rec.p, reflected);
    attenuation = albedo_;
    return (dot(ray_scattered.direction(), rec.normal) > 0);
  }

 private:
  Color albedo_;
  double fuzz_ = 0.0;
};

class Dielectric : public Material {
 public:
  Dielectric(double refraction_index) : refraction_index_(refraction_index) {}

  bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation,
               Ray& ray_scattered) const override {
    attenuation = Color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index_) : refraction_index_;

    Vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract)
      direction = reflect(unit_direction, rec.normal);
    else
      direction = refract(unit_direction, rec.normal, ri);

    ray_scattered = Ray(rec.p, direction);
    return true;
  }

 private:
  // Refractive index in vacuum or air, or the ratio of the material's refractive index over
  // the refractive index of the enclosing media
  double refraction_index_;
};

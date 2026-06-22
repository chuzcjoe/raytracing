#include "Camera.h"

void Camera::Render(const HitBase& world) {
  Initialize();

  std::cout << "P3\n" << image_width << ' ' << image_height_ << "\n255\n";

  for (int j = 0; j < image_height_; j++) {
    for (int i = 0; i < image_width; i++) {
      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      Ray r(center_, pixel_center - center_);
      WriteColor(std::cout, RayColor(r, world));
    }
  }
}

void Camera::Initialize() {
  image_height_ = int(image_width / aspect_ratio);
  image_height_ = (image_height_ < 1) ? 1 : image_height_;

  center_ = Point3(0, 0, 0);

  // Determine viewport dimensions.
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height_);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  auto viewport_u = Vec3(viewport_width, 0, 0);
  auto viewport_v = Vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height_;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left = center_ - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Color Camera::RayColor(const Ray& r, const HitBase& world) const {
  HitRecord rec;
  if (world.Hit(r, Interval(0, infinity), rec)) {
    return 0.5 * (rec.normal + Color(1, 1, 1));
  }

  Vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
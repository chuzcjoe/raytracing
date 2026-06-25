#include "Camera.h"
#include "Material.h"

void Camera::Render(const HitBase& world) {
  Initialize();

  std::cout << "P3\n" << image_width << ' ' << image_height_ << "\n255\n";

  for (int j = 0; j < image_height_; j++) {
    for (int i = 0; i < image_width; i++) {
      Color pixel_color(0, 0, 0);
      for (int sample = 0; sample < samples_per_pixel; ++sample) {
        Ray r = GetRay(i, j);
        pixel_color += RayColor(r, max_depth, world);
      }

      WriteColor(std::cout, pixel_samples_scale_ * pixel_color);
    }
  }
}

void Camera::Initialize() {
  image_height_ = int(image_width / aspect_ratio);
  image_height_ = (image_height_ < 1) ? 1 : image_height_;
  pixel_samples_scale_ = 1.0 / samples_per_pixel;

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

Ray Camera::GetRay(int i, int j) const {
  // Construct a camera ray originating from the origin and directed at randomly sampled
  // point around the pixel location i, j.

  auto offset = SampleSquare();
  auto pixel_sample =
      pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

  auto ray_origin = center_;
  auto ray_direction = pixel_sample - ray_origin;

  return Ray(ray_origin, ray_direction);
}

Color Camera::RayColor(const Ray& r, const int depth, const HitBase& world) const {
  if (depth <= 0) return Color(0, 0, 0);

  HitRecord rec;
  // use a small t_min value to avoid self-intersection with the surface.
  if (world.Hit(r, Interval(0.001, infinity), rec)) {
    Ray scattered;
    Color attenuation;
    if (rec.material->Scatter(r, rec, attenuation, scattered))
        return attenuation * RayColor(scattered, depth - 1, world);
    return Color(0,0,0);
  }

  Vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

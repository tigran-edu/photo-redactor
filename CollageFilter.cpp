#include "CollageFilter.h"
#include "cmath"

Image CollageFilter::Apply(const Image &image) {
    std::cout << "CollageFilter start" << std::endl;
    CompressionFilter compression;
    Image small_image = compression.Apply(image);
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    Image answer(width, height);
    int32_t width_of_pixel = std::max(2.0, std::ceil(width / 150.0));
    int32_t height_of_pixel = std::max(2.0, std::ceil(height / 150.0));
    for (int32_t y = height_of_pixel; y < height; y += 2 * height_of_pixel + 1) {
        for (int32_t x = width_of_pixel; x < width; x += 2 * width_of_pixel + 1) {
            Pixel tmp_pixel = image.GetPixel(x, y);
            ShadeFilter shade(tmp_pixel);
            Image tmp_image = shade.Apply(small_image);
            for (int tmp_y = -height_of_pixel; tmp_y <= std::min(height_of_pixel, height - y - 1); ++tmp_y) {
                for (int tmp_x = -width_of_pixel; tmp_x <= std::min(width_of_pixel, width - x - 1); ++tmp_x) {
                    answer.RewritePixel(tmp_image.GetPixel(width_of_pixel + tmp_x, height_of_pixel + tmp_y), x + tmp_x,
                                        y + tmp_y);
                }
            }
        }
    }
    std::cout << "CollageFilter end" << std::endl;
    return answer;
}

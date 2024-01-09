#include "PixelFilter.h"
#include "cmath"

Image PixelFilter::Apply(const Image &image) {
    std::cout << "PixelFilter start" << std::endl;
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    int32_t center_of_small_pixel_x = 0;
    int32_t center_of_small_pixel_y = 0;
    if (width_of_pixel_ % 2 != 0) {
        center_of_small_pixel_x = (width_of_pixel_ - 1) / 2;
    } else {
        center_of_small_pixel_x = width_of_pixel_ / 2;
    }
    if (height_of_pixel_ % 2 != 0) {
        center_of_small_pixel_y = (height_of_pixel_ - 1) / 2;
    } else {
        center_of_small_pixel_y = height_of_pixel_ / 2;
    }
    Image tmp_image(width, height);
    for (int32_t y = height_of_pixel_; y < height; y += height_of_pixel_) {
        for (int32_t x = width_of_pixel_; x < width; x += width_of_pixel_) {
            Pixel tmp_pixel = image.GetPixel(x, y);
            for (int tmp_y = -center_of_small_pixel_y; tmp_y <= std::min(center_of_small_pixel_y, height - y - 1); ++tmp_y) {
                for (int tmp_x = -center_of_small_pixel_x; tmp_x <= std::min(center_of_small_pixel_x, width - x - 1); ++tmp_x) {
                    tmp_image.RewritePixel(tmp_pixel, x + tmp_x, y + tmp_y);
                }
            }
        }
    }
    std::cout << "PixelFilter end" << std::endl;
    return tmp_image;
}

PixelFilter::PixelFilter(int32_t width, int32_t height)  : width_of_pixel_(width), height_of_pixel_(height) {}



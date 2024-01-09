#include "CompressionFilter.h"
#include "cmath"


Image CompressionFilter::Apply(const Image &image) {
    std::cout << "CompressionFilter start" << std::endl;
    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();
    const int32_t width_of_pixel = 2 * std::max(2.0, std::ceil(width / 150.0)) + 1;
    const int32_t height_of_pixel = 2 * std::max(2.0, std::ceil(height / 150.0)) + 1;
    const int32_t skip_x = width / width_of_pixel;
    const int32_t skip_y = height / height_of_pixel;
    Image tmp_image(width_of_pixel, height_of_pixel);
    int32_t y = 0;
    for (int32_t count_y = 0; count_y < height_of_pixel; ++count_y) {
        int32_t x = 0;
        for (int32_t count_x = 0; count_x < width_of_pixel; ++count_x) {
            Pixel tmp_pixel = image.GetPixel(x, y);
            tmp_image.RewritePixel(tmp_pixel, count_x, count_y);
            x += skip_x;
        }
        y += skip_y;
    }
    std::cout << "CompressionFilter end" << std::endl;
    return tmp_image;
}

#include "NegativeFilter.h"

Image NegativeFilter::Apply(const Image &image) {
    std::cout << "Negative Filter start" << std::endl;
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    Image tmp_image(width, height);
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            Pixel tmp_pixel = image.GetPixel(x, y);
            tmp_pixel.blue = 255 - tmp_pixel.blue;
            tmp_pixel.green = 255 - tmp_pixel.green;
            tmp_pixel.red = 255 - tmp_pixel.red;
            tmp_image.RewritePixel(tmp_pixel, x, y);
        }
    }
    std::cout << "Negative Filter end" << std::endl;
    return tmp_image;
}

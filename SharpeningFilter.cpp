#include "SharpeningFilter.h"

Image SharpeningFilter::Apply(const Image &image) {
    std::cout << "Sharpening Filter start" << std::endl;
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    Image tmp_image(width, height);
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            DoublePixel tmp_double_pixel;
            tmp_double_pixel = ApplyMatrixForPixel(x, y, matrix_arr_, image);
            Pixel tmp_pixel;
            tmp_pixel.blue = static_cast<uint8_t>(tmp_double_pixel.blue * 255.0);
            tmp_pixel.green = static_cast<uint8_t>(tmp_double_pixel.green * 255.0);
            tmp_pixel.red = static_cast<uint8_t>(tmp_double_pixel.red * 255.0);
            tmp_image.RewritePixel(tmp_pixel, x, y);
        }
    }
    std::cout << "Sharpening Filter end" << std::endl;
    return tmp_image;
}

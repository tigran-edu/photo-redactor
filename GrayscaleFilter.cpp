#include "GrayscaleFilter.h"

Image GrayscaleFilter::Apply(const Image &image) {
    std::cout << "Grayscale start" << std::endl;
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    Image tmp_image(width, height);
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            Pixel tmp_pixel = image.GetPixel(x, y);
            DoublePixel tmp_double_pixel = tmp_pixel.ConvertToDouble();
            tmp_pixel.red = static_cast<uint8_t>(
                    (0.144 * tmp_double_pixel.blue + 0.587 * tmp_double_pixel.green +
                     0.299 * tmp_double_pixel.red) * 255.0);
            tmp_pixel.green = tmp_pixel.red;
            tmp_pixel.blue = tmp_pixel.red;
            tmp_image.RewritePixel(tmp_pixel, x, y);
        }
    }
    std::cout << "Grayscale end" << std::endl;
    return tmp_image;
}

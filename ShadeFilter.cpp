#include "ShadeFilter.h"
#include "cmath"

Image ShadeFilter::Apply(const Image &image) {
    std::cout << "ShadeFilter start" << std::endl;
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    Image answer(width, height);
    double coeff = pow(765.0, 0.5);
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            Pixel tmp_pixel = image.GetPixel(x, y);
            double summa = pow(static_cast<double>(tmp_pixel.blue + tmp_pixel.green + tmp_pixel.red), 0.5);

            tmp_pixel.blue = static_cast<int32_t>(summa * (blue_ / coeff));
            tmp_pixel.red = static_cast<int32_t>(summa * (red_ / coeff));
            tmp_pixel.green = static_cast<int32_t>(summa * (green_ / coeff));
            answer.RewritePixel(tmp_pixel, x, y);
        }
    }
    std::cout << "ShadeFilter end" << std::endl;
    return answer;
}

ShadeFilter::ShadeFilter(const Pixel &pixel) {
    red_ = static_cast<double>(pixel.red);
    green_ = static_cast<double >(pixel.green);
    blue_ = static_cast<double>(pixel.blue);
}

ShadeFilter::ShadeFilter(int32_t red, int32_t green, int32_t blue) : blue_(blue), green_(green), red_(red) {}

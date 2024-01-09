#include <cmath>
#include "GaussianBlurFilter.h"

Image GaussianBlurFilter::Apply(const Image &image) {
    if (sigma_ == 0) {
        return image;
    }
    std::cout << "GaussianFilter start" << std::endl;
    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    Image tmp_image(width, height);
    Image answer(width, height);
    std::vector<double> exp_coeff(static_cast<int32_t>(6 * sigma_ + 5));
    double summ = 0;
    int32_t tmp_sigma = static_cast<int32_t>(3 * sigma_ + 2);
    for (int32_t i = 0; i < 2 * tmp_sigma + 1; ++i) {
        exp_coeff[i] = exp(-pow(-3 * sigma_ - 2 + i, 2) / (2 * pow(sigma_, 2)))  / (pow(2 * M_PI, 0.5) * sigma_);
        summ += exp_coeff[i];
    }
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            Pixel pixel;
            DoublePixel double_pixel;
            int32_t left = std::min(x, tmp_sigma);
            int32_t right = std::min(width - x - 1, tmp_sigma);
            for (int32_t i = -left; i <= right; ++i) {
                Pixel tmp_pixel = image.GetPixel(x + i, y);
                DoublePixel tmp_double_pixel = tmp_pixel.ConvertToDouble();
                double_pixel += tmp_double_pixel * exp_coeff[tmp_sigma + i];
            }
            double_pixel = double_pixel * (1 / summ);
            pixel = double_pixel.Clamp();
            tmp_image.RewritePixel(pixel, x, y);
        }
    }
    for (int32_t x = 0; x < width; ++x) {
        for (int32_t y = 0; y < height; ++y) {
            Pixel pixel;
            DoublePixel double_pixel;
            int32_t top = std::min(y, tmp_sigma);
            int32_t low = std::min(height - y - 1, tmp_sigma);
            for (int32_t i = -top; i <= low; ++i) {
                Pixel tmp_pixel = tmp_image.GetPixel(x, y + i);
                DoublePixel tmp_float_pixel = tmp_pixel.ConvertToDouble();
                double_pixel += tmp_float_pixel * exp_coeff[tmp_sigma + i];
            }
            double_pixel = double_pixel * (1 / summ);
            pixel = double_pixel.Clamp();
            answer.RewritePixel(pixel, x, y);
        }
    }
    std::cout << "GaussianFilter end" << std::endl;
    return answer;
}

GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    sigma_ = sigma;
}

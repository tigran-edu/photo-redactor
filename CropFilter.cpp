#include "CropFilter.h"

Image CropFilter::Apply(const Image &image) {
    std::cout << "CropFilter start" << std::endl;
    height_ = std::min(image.GetHeight(), height_);
    width_ = std::min(image.GetWidth(), width_);
    Image tmp_image(width_, height_);
    for (int32_t y = 0; y < height_; ++y) {
        for (int32_t x = 0; x < width_; ++x) {
            tmp_image.RewritePixel(image.GetPixel(x, image.GetHeight() - 1 - y), x,
                                   height_ - y - 1);
        }
    }
    std::cout << "CropFilter end" << std::endl;
    return tmp_image;
}

CropFilter::CropFilter(int32_t width, int32_t height) {
    width_ = width;
    height_ = height;
}

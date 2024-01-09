#include "Image.h"

Image::Image() {}

Pixel Image::GetPixel(int32_t x, int32_t y) const {
    return pixels_[y][x];
}

int32_t Image::GetWidth() const {
    return pixels_[0].size();
}

int32_t Image::GetHeight() const {
    return pixels_.size();
}

void Image::RewritePixel(const Pixel &other_pixel, int32_t x, int32_t y) {
    pixels_[y][x].red = other_pixel.red;
    pixels_[y][x].green = other_pixel.green;
    pixels_[y][x].blue = other_pixel.blue;
}

Image::Image(const Image &other) {
    pixels_ = other.pixels_;
}

Image &Image::operator=(const Image &other) {
    if (this == &other) {
        return *this;
    }
    pixels_ = other.pixels_;
    return *this;
}

Image::Image(int32_t width, int32_t height) {
    height = std::abs(height);
    pixels_.resize(height);
    for (int32_t i = 0; i < height; ++i) {
        pixels_[i].resize(width);
    }
}

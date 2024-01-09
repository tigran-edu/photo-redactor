#include "Pixels.h"

Pixel::Pixel() {
    red = 0;
    blue = 0;
    green = 0;
}

Pixel::Pixel(uint8_t red_color, uint8_t green_color, uint8_t blue_color) {
    red = red_color;
    green = green_color;
    blue = blue_color;
}

DoublePixel Pixel::ConvertToDouble() {
    DoublePixel tmp_pixel;
    tmp_pixel.blue = static_cast<double>(blue) / 255.0;
    tmp_pixel.green = static_cast<double>(green) / 255.0;
    tmp_pixel.red = static_cast<double>(red) / 255.0;
    return tmp_pixel;
}


DoublePixel::DoublePixel() {
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

DoublePixel& DoublePixel::operator=(const DoublePixel &other) {
    green = other.green;
    blue = other.blue;
    red = other.red;
    return *this;
}

DoublePixel& DoublePixel::operator+=(const DoublePixel &other) {
    red += other.red;
    green += other.green;
    blue += other.blue;
    return *this;
}

Pixel DoublePixel::Clamp() {
    Pixel tmp_pixel;
    tmp_pixel.blue = static_cast<uint8_t>(255.0 * std::min(1.0, std::max(0.0, blue)));
    tmp_pixel.green = static_cast<uint8_t>(255.0 * std::min(1.0, std::max(0.0, green)));
    tmp_pixel.red = static_cast<uint8_t>(255.0 * std::min(1.0, std::max(0.0, red)));
    return tmp_pixel;
}



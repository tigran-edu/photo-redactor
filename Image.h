#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "Pixels.h"


class Image {
public:
    Image();

    Image(int32_t width, int32_t height);

    void RewritePixel(const Pixel &other_pixel, int32_t x, int32_t y);

    Image &operator=(const Image &other);

    Image(const Image &other);

    Pixel GetPixel(int32_t x, int32_t y) const;

    int32_t GetWidth() const;

    int32_t GetHeight() const;

private:
    std::vector<std::vector<Pixel>> pixels_;
};

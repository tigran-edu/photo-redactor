#pragma once

#include <iostream>

struct Pixel;

struct DoublePixel {
    DoublePixel();

    template<typename T>
    DoublePixel operator*(T coeff) {
        DoublePixel other;
        coeff = static_cast<double>(coeff);
        other.blue = blue * coeff;
        other.green = green * coeff;
        other.red = red * coeff;
        return other;
    }

    DoublePixel& operator+=(const DoublePixel &other);

    DoublePixel& operator=(const DoublePixel &other);

    Pixel Clamp();

    double red = 0;
    double green = 0;
    double blue = 0;
};


struct Pixel {
    Pixel();

    Pixel(uint8_t red_color, uint8_t green_color, uint8_t blue_color);

    DoublePixel ConvertToDouble();


    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
};
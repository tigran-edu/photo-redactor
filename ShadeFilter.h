#pragma once
#include "Filter.h"

class ShadeFilter : public Filter {
public:
    Image Apply(const Image &image) override;
    ShadeFilter(const Pixel& pixel);
    ShadeFilter(int32_t red, int32_t green, int32_t blue);

private:
    float blue_ = 0;
    float green_ = 0;
    float red_ = 0;
};


